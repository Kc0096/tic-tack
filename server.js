const express = require("express");
const { execFile } = require("child_process");
const path = require("path");
const app = express();

app.use(express.static(".")); // serve index.html, css, js

app.get("/move/:pos", (req, res) => {
    execFile(path.join(__dirname, "server.exe"), [req.params.pos], (err, stdout) => {
        if (err) {
            res.status(500).send("Error running C++ backend");
            return;
        }
        res.setHeader("Content-Type", "application/json");
        res.send(stdout);
    });
});

app.listen(3000, () => console.log("Server running at http://localhost:3000"));
