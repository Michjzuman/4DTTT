// Minimal 4DTTT framework + hover-highlighting for sub-cells
// Framework structure: App -> Game -> Board -> Cell

const App = (() => {
    const state = {
        canvas: null,
        ctx: null,
        dpr: 1,
        game: null,
    };

    function getCSSVar(name) {
        return getComputedStyle(document.documentElement).getPropertyValue(name).trim() || null;
    }

    const colors = {
        get black() { return getCSSVar('--black'); },
        get white() { return getCSSVar('--white'); },
        get red() { return getCSSVar('--red'); },
        get green() { return getCSSVar('--green'); },
        get blue() { return getCSSVar('--blue'); },
    };

    function resizeCanvas() {
        const canvas = state.canvas;
        const ctx = state.ctx;
        state.dpr = window.devicePixelRatio || 1;

        const cssWidth = canvas.clientWidth;
        const cssHeight = canvas.clientHeight;
        canvas.width = Math.round(cssWidth * state.dpr);
        canvas.height = Math.round(cssHeight * state.dpr);

        // Use CSS-space coordinates for drawing
        ctx.setTransform(state.dpr, 0, 0, state.dpr, 0, 0);

        if (state.game) {
            state.game.layout();
            state.game.draw();
        }
    }

    function onMouseMove(e) {
        if (!state.game) return;
        const rect = state.canvas.getBoundingClientRect();
        const x = e.clientX - rect.left; // CSS px
        const y = e.clientY - rect.top;  // CSS px
        if (state.game.handleMouseMove(x, y)) {
            state.game.draw();
        }
    }

    function init() {
        state.canvas = document.querySelector('.game');
        state.ctx = state.canvas.getContext('2d');
        state.game = new Game(state.canvas, state.ctx, colors);

        window.addEventListener('resize', resizeCanvas);
        state.canvas.addEventListener('mousemove', onMouseMove);

        resizeCanvas();
    }

    return { init };
})();

class Game {
    constructor(canvas, ctx, colors) {
        this.canvas = canvas;
        this.ctx = ctx;
        this.colors = colors;
        this.board = new Board();

        // Layout constants (in CSS px)
        this.padRatio = 0.08; // outer padding ratio of min(w,h)
        this.margin = 5;      // spacing between groups and cells
    }

    layout() {
        const w = this.canvas.clientWidth;
        const h = this.canvas.clientHeight;

        const pad = Math.floor(Math.min(w, h) * this.padRatio);
        const size = Math.min(w, h) - pad * 2; // square board side
        const bx = pad;
        const by = pad;

        // Each of the 3x3 big squares has outer size (including its margin to next)
        const bigStep = size / 3 - this.margin;
        const bigInner = size / 3 - (this.margin * 2); // actual stroked rect of big square

        // Each small cell inside a big square
        const cellSide = (bigInner - this.margin * 4) / 3;

        // Build rectangles for hit detection and drawing
        this.board.reset();
        for (let gy = 0; gy < 3; gy++) {
            for (let gx = 0; gx < 3; gx++) {
                const bigX = bx + gx * (bigStep + this.margin) + 0.5;
                const bigY = by + gy * (bigStep + this.margin) + 0.5;
                const bigRect = { x: bigX, y: bigY, w: bigInner, h: bigInner };
                const group = new CellGroup(bigRect);

                for (let cy = 0; cy < 3; cy++) {
                    for (let cx = 0; cx < 3; cx++) {
                        const sx = bigRect.x + this.margin + cx * (this.margin + cellSide);
                        const sy = bigRect.y + this.margin + cy * (this.margin + cellSide);
                        const rect = { x: sx, y: sy, w: cellSide, h: cellSide };
                        group.addCell(new Cell(rect));
                    }
                }
                this.board.addGroup(group);
            }
        }

        this.board.bounds = { x: bx, y: by, w: size, h: size };
    }

    clear() {
        const w = this.canvas.clientWidth;
        const h = this.canvas.clientHeight;
        this.ctx.clearRect(0, 0, w, h);
        this.ctx.fillStyle = this.colors.black;
        this.ctx.fillRect(0, 0, w, h);
    }

    draw() {
        const ctx = this.ctx;
        this.clear();

        // Board background (optional visual)
        const b = this.board.bounds;
        ctx.fillStyle = this.colors.black;
        ctx.fillRect(b.x, b.y, b.w, b.h);

        // Draw 3x3 big squares
        ctx.lineWidth = 1;
        for (const group of this.board.groups) {
            ctx.strokeStyle = this.colors.white;
            ctx.strokeRect(group.rect.x, group.rect.y, group.rect.w, group.rect.h);

            // Draw 3x3 inner cells with hover highlight
            for (const cell of group.cells) {
                ctx.strokeStyle = cell.isHovered ? this.colors.red : this.colors.white;
                ctx.strokeRect(cell.rect.x, cell.rect.y, cell.rect.w, cell.rect.h);
            }
        }
    }

    handleMouseMove(x, y) {
        // Returns true if hover state changed
        let changed = false;
        for (const group of this.board.groups) {
            for (const cell of group.cells) {
                const inside = pointInRect(x, y, cell.rect);
                if (inside !== cell.isHovered) {
                    cell.isHovered = inside;
                    changed = true;
                }
            }
        }
        return changed;
    }
}

class Board {
    constructor() {
        this.groups = []; // 9 big squares
        this.bounds = { x: 0, y: 0, w: 0, h: 0 };
    }
    addGroup(g) { this.groups.push(g); }
    reset() { this.groups.length = 0; }
}

class CellGroup {
    constructor(rect) {
        this.rect = rect; // {x,y,w,h}
        this.cells = [];  // 9 small cells
    }
    addCell(c) { this.cells.push(c); }
}

class Cell {
    constructor(rect) {
        this.rect = rect; // {x,y,w,h}
        this.isHovered = false;
    }
}

function pointInRect(x, y, r) {
    return x >= r.x && y >= r.y && x <= r.x + r.w && y <= r.y + r.h;
}

// Boot
App.init();