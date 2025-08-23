

(() => {
    const canvas = document.querySelector('.game');
    const ctx = canvas.getContext('2d');

    function getCSSVar(name) {
        return getComputedStyle(document.documentElement).getPropertyValue(name).trim() || null;
    }

    const colors = {
        bg: getCSSVar('--bg') || '#23242c',
        game: getCSSVar('--game-color') || '#282828',
        board: getCSSVar('--board-color') || '#1e1e1e',
        border: getCSSVar('--border-color') || '#3c3c3c'
    };

    function resizeCanvas() {
        const dpr = window.devicePixelRatio || 1;
        const cssWidth = canvas.clientWidth;
        const cssHeight = canvas.clientHeight;

        canvas.width = Math.round(cssWidth * dpr);
        canvas.height = Math.round(cssHeight * dpr);

        // Scale drawing so 1 unit = 1 CSS pixel for crisp lines
        ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
        drawBoard();
    }

    function drawBoard() {
        const w = canvas.clientWidth;
        const h = canvas.clientHeight;

        // Clear & background
        ctx.clearRect(0, 0, w, h);
        ctx.fillStyle = colors.game;
        ctx.fillRect(0, 0, w, h);

        // Board square
        const pad = Math.floor(Math.min(w, h) * 0.08);
        const x = pad;
        const y = pad;
        const size = Math.min(w, h) - pad * 2;

        // Board background
        ctx.fillStyle = colors.board;
        ctx.fillRect(x, y, size, size);

        // Outer border
        ctx.strokeStyle = colors.border;
        ctx.lineWidth = 2;
        ctx.strokeRect(x + 0.5, y + 0.5, size - 1, size - 1);

        // Grid lines for 9x9 board (8 inner lines per direction)
        const cells = 9;
        const step = size / cells;

        ctx.beginPath();
        for (let i = 1; i < cells; i++) {
            const gx = Math.round(x + i * step) + 0.5;
            ctx.moveTo(gx, y);
            ctx.lineTo(gx, y + size);

            const gy = Math.round(y + i * step) + 0.5;
            ctx.moveTo(x, gy);
            ctx.lineTo(x + size, gy);
        }
        ctx.strokeStyle = colors.border;
        ctx.lineWidth = 1;
        ctx.stroke();
    }

    window.addEventListener('resize', resizeCanvas);
    resizeCanvas();
})();