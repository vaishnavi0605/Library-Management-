const session = require('express-session');
const express = require('express');
const bodyParser = require('body-parser');
const { execFile } = require('child_process');
const path = require('path');

const app = express();
const port = 3000;
// Middleware to handle sessions
app.use(session({
    secret: 'library_secret_key',
    resave: false,
    saveUninitialized: true,
    cookie: { secure: false } // set true if using HTTPS
}));

app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.json());
app.use(express.static(path.join(__dirname, '../public')));

const binDir = path.join(__dirname, '../bin');

const requireRole = (role) => (req, res, next) => {
    if (!req.session.user || req.session.user.role !== role) {
        return res.status(403).send("Access denied");
    }
    next();
};

// === Issue Book ===
app.post('/api/issue', requireRole('student'), (req, res) => {
    const studentId = req.session.user.id; // ✅ from session
    const { title } = req.body;
    const exePath = path.join(binDir, 'issue.exe');

    execFile(exePath, [studentId, title], (err, stdout, stderr) => {
        if (err) return res.status(500).send(stderr);
        res.send(stdout);
    });
});



// === Return Book ===
app.post('/api/return', requireRole('student'), (req, res) => {
    const studentId = req.session.user.id;
    const { title } = req.body;
    const exePath = path.join(binDir, 'return.exe');

    execFile(exePath, [studentId, title], (err, stdout, stderr) => {
        if (err) return res.status(500).send(stderr);
        res.send(stdout);
    });
});



app.listen(port, () => {
    console.log(` Server running at http://localhost:${port}`);
});

// === Search Book ===
app.post('/api/search', (req, res) => {
    const { title } = req.body;
    const exePath = path.join(binDir, 'search.exe');

    execFile(exePath, [title], (err, stdout, stderr) => {
        if (err) return res.status(500).send(stderr);
        res.send(stdout);
    });
});

// === Add Book ===
app.post('/api/login', (req, res) => {
    const { id, role } = req.body;
    const exePath = path.join(binDir, 'login.exe');

    execFile(exePath, [id, role], (err, stdout, stderr) => {
        if (err) return res.status(401).send("Login failed");

        // Store session info
        req.session.user = { id, role };
        res.send(stdout);
    });
});

// === Logout ===
app.post('/api/logout', (req, res) => {
    req.session.destroy((err) => {
        if (err) {
            return res.status(500).send("Logout failed");
        }
        res.clearCookie('connect.sid'); // optional, to clear session cookie
        res.send("Logged out successfully");
    });
});



app.post('/api/add-book', requireRole('faculty'), (req, res) => {
    const { title, author } = req.body;
    const exePath = path.join(binDir, 'add-book.exe');

    execFile(exePath, [title, author], (err, stdout, stderr) => {
        if (err) return res.status(500).send(stderr);
        res.send(stdout);
    });
});

app.post('/api/delete-book', requireRole('faculty'), (req, res) => {
    const { title } = req.body;
    const exePath = path.join(binDir, 'delete-book.exe');

    execFile(exePath, [title], (err, stdout, stderr) => {
        if (err) return res.status(500).send(stderr);
        res.send(stdout);
    });
});
        
    


app.post('/api/delete-book', requireRole('faculty'), (req, res) => {
    const { title } = req.body;
    const exePath = path.join(binDir, 'delete-book.exe');

    execFile(exePath, [title], (err, stdout, stderr) => {
        if (err) return res.status(500).send(stderr);
        res.send(stdout);
    });
});

app.get('/api/my-books', requireRole('student'), (req, res) => {
    const studentId = req.session.user.id;
    const exePath = path.join(binDir, 'my-books.exe');

    execFile(exePath, [studentId], (err, stdout, stderr) => {
        if (err) return res.status(500).send(stderr);
        res.send(stdout);
    });
});


