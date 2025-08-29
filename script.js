let board = ["", "", "", "", "", "", "", "", ""];
let currentPlayer = "X";
let gameActive = false;
let playerX = "Player X";
let playerO = "Player O";

const cells = document.querySelectorAll(".cell");
const statusDisplay = document.getElementById("status");

function startGame() {
  playerX = document.getElementById("playerX").value || "Player X";
  playerO = document.getElementById("playerO").value || "Player O";
  board = ["", "", "", "", "", "", "", "", ""];
  currentPlayer = "X";
  gameActive = true;
  statusDisplay.innerHTML = `${playerX}'s turn`;
  cells.forEach(cell => {
    cell.innerText = "";
    cell.classList.remove("taken");
  });
}

cells.forEach(cell => {
  cell.addEventListener("click", () => {
    if (!gameActive) return;
    const index = cell.getAttribute("data-index");
    if (board[index] !== "") return;
    board[index] = currentPlayer;
    cell.innerText = currentPlayer;
    cell.classList.add("taken");

    if (checkWin()) {
      gameActive = false;
      statusDisplay.innerHTML = currentPlayer === "X" ? `${playerX} Wins! 🎉` : `${playerO} Wins! 🎉`;
      return;
    }

    if (!board.includes("")) {
      gameActive = false;
      statusDisplay.innerHTML = "It's a Draw! 🤝";
      return;
    }

    currentPlayer = currentPlayer === "X" ? "O" : "X";
    statusDisplay.innerHTML = currentPlayer === "X" ? `${playerX}'s turn` : `${playerO}'s turn`;
  });
});

function checkWin() {
  const winPatterns = [
    [0,1,2],[3,4,5],[6,7,8],
    [0,3,6],[1,4,7],[2,5,8],
    [0,4,8],[2,4,6]
  ];
  return winPatterns.some(pattern => {
    const [a, b, c] = pattern;
    return board[a] && board[a] === board[b] && board[a] === board[c];
  });
}

function resetGame() {
  startGame();
}
