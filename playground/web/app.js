"use strict";

const data = globalThis.ivriSamples;
const sample = document.querySelector("#sample");
const run = document.querySelector("#run");
const commandInput = document.querySelector("#commands");
const inputPanel = document.querySelector("#input-panel");
const output = document.querySelector("#output");
const status = document.querySelector("#status");
const initialCommands = "הוסף 10\nהוסף 30\nחשב\nיציאה";
const keywords = new Set([
    ...Object.keys(data.keywords),
    ...Object.values(data.keywords).flatMap(value => value.split(" ")),
    "include", "throw", "explicit", "static_cast", "class", "for", "if", "else",
]);
const codeTokens = /\/\/[^\n]*|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|[\p{L}_][\p{L}\p{N}_]*|\b\d+(?:\.\d+)?\b/gu;
const compiled = new Map();

function showCode(element, code) {
    const fragment = document.createDocumentFragment();
    let previousEnd = 0;
    for (const match of code.matchAll(codeTokens)) {
        const token = match[0];
        fragment.append(code.slice(previousEnd, match.index));
        const isHebrew = /^[\p{Script=Hebrew}_]+$/u.test(token) && /\p{Script=Hebrew}/u.test(token);
        if (isHebrew || keywords.has(token) || /^["'\d]/.test(token) || token.startsWith("//")) {
            const span = document.createElement(isHebrew ? "bdi" : "span");
            if (isHebrew) span.dir = "rtl";
            if (keywords.has(token)) span.className = "token-keyword";
            else if (token.startsWith("//")) span.className = "token-comment";
            else if (!isHebrew) span.className = "token-literal";
            span.textContent = token;
            fragment.append(span);
        } else {
            fragment.append(token);
        }
        previousEnd = match.index + token.length;
    }
    fragment.append(code.slice(previousEnd));
    element.replaceChildren(fragment);
}

function showOutput(text) {
    const fragment = document.createDocumentFragment();
    const numericLists = /\[(?:-?\d+(?:, -?\d+)*)?\]/g;
    let previousEnd = 0;
    for (const match of text.matchAll(numericLists)) {
        fragment.append(text.slice(previousEnd, match.index));
        const list = document.createElement("bdi");
        list.dir = "ltr";
        list.textContent = match[0];
        fragment.append(list);
        previousEnd = match.index + match[0].length;
    }
    fragment.append(text.slice(previousEnd));
    output.replaceChildren(fragment);
}

// Only the WASI calls used by these examples are provided. FDs 0–2 map to
// the input field and output panel, with no filesystem or environment access.
function runProgram(module, stdin) {
    const input = new TextEncoder().encode(stdin);
    const decoder = new TextDecoder();
    let offset = 0;
    let result = "";
    let instance;
    let exitCode = 0;
    const programExit = new Error("WASI process exit");

    function memory() {
        return new DataView(instance.exports.memory.buffer);
    }

    function moveBytes(vectors, count, resultPointer, copy) {
        const view = memory();
        let total = 0;
        for (let index = 0; index < count; index++) {
            const address = vectors + index * 8;
            const pointer = view.getUint32(address, true);
            const length = view.getUint32(address + 4, true);
            const moved = copy(new Uint8Array(view.buffer, pointer, length));
            total += moved;
            if (moved < length) break;
        }
        view.setUint32(resultPointer, total, true);
        return 0;
    }

    instance = new WebAssembly.Instance(module, {
        wasi_snapshot_preview1: {
            environ_get: () => 0,
            environ_sizes_get: (count, bytes) => {
                const view = memory();
                view.setUint32(count, 0, true);
                view.setUint32(bytes, 0, true);
                return 0;
            },
            fd_close: fd => fd <= 2 ? 0 : 8,
            fd_fdstat_get: (fd, pointer) => {
                if (fd > 2) return 8;
                const view = memory();
                new Uint8Array(view.buffer, pointer, 24).fill(0);
                view.setUint8(pointer, 2); // Character device.
                view.setBigUint64(pointer + 8, fd === 0 ? 2n : 64n, true);
                return 0;
            },
            fd_read: (fd, vectors, count, read) => {
                if (fd !== 0) return 8;
                return moveBytes(vectors, count, read, target => {
                    const chunk = input.subarray(offset, offset + target.length);
                    target.set(chunk);
                    offset += chunk.length;
                    return chunk.length;
                });
            },
            fd_seek: () => 70, // ESPIPE.
            fd_write: (fd, vectors, count, written) => {
                if (fd !== 1 && fd !== 2) return 8;
                return moveBytes(vectors, count, written, bytes => {
                    result += decoder.decode(bytes, { stream: true });
                    return bytes.length;
                });
            },
            proc_exit: code => {
                exitCode = code;
                throw programExit;
            },
        },
    });

    try {
        instance.exports._start();
    } catch (error) {
        if (error !== programExit) throw error;
    }
    return { text: result + decoder.decode(), exitCode };
}

async function runSelected() {
    const key = sample.value;
    const commands = key === "terminal" ? commandInput.value + "\n" : "";
    run.disabled = true;
    output.textContent = "";
    status.textContent = "מריץ…";
    status.dataset.state = "running";
    try {
        if (!compiled.has(key)) {
            const bytes = Uint8Array.from(atob(data.examples[key].wasm), char => char.charCodeAt(0));
            compiled.set(key, WebAssembly.compile(bytes));
        }
        const module = await compiled.get(key);
        if (sample.value !== key) return;
        const result = runProgram(module, commands);
        showOutput(result.text);
        status.textContent = result.exitCode === 0 ? "ההרצה הסתיימה" : "קוד יציאה " + result.exitCode;
        status.dataset.state = result.exitCode === 0 ? "success" : "error";
    } catch (error) {
        if (sample.value !== key) return;
        compiled.delete(key);
        status.textContent = "ההרצה נכשלה";
        status.dataset.state = "error";
        output.textContent = error.message;
    } finally {
        if (sample.value === key) run.disabled = false;
    }
}

function selectExample() {
    const example = data.examples[sample.value];
    document.querySelector("#summary").textContent = example.summary;
    document.querySelector("#source").href =
        "https://github.com/DorManDel/Ivri-/blob/main/examples/" + example.file;
    showCode(document.querySelector("#hebrew-code"), example.hebrew);
    showCode(document.querySelector("#cpp-code"), example.cpp);
    inputPanel.hidden = sample.value !== "terminal";
    runSelected();
}

commandInput.value = initialCommands;
run.addEventListener("click", runSelected);
sample.addEventListener("change", selectExample);
document.querySelector("#reset").addEventListener("click", () => {
    commandInput.value = initialCommands;
    commandInput.focus();
});
selectExample();
