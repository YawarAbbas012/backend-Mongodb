const express = require('express');
const User = require('./models/signup');
const Game = require('./models/game'); 
const Order = require('./models/order'); // Import the Order model
const path = require('path'); //
const mongoose = require('mongoose');
const bodyParser = require('body-parser');
const session = require('express-session');

const app = express();

app.set('view engine', 'ejs');

mongoose.connect('mongodb://localhost:27017/gameing_zone').then(() => {
    console.log("Connected ♥");
}).catch((error) => {
    console.error('Database connection error:', error);
});

const port = 4000;

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.use(express.static(path.join(__dirname, 'public')));

app.use(session({
    secret: 'Habib',
    resave: true,
    saveUninitialized: true
}));

// Render home page with games
app.get('/home', isAuthenticated, async (req, res) => {
    try {
        const games = await Game.find({});
        res.render('home', { games });
    } catch (error) {
        console.error('Error fetching games:', error);
        res.status(500).send('Error fetching games. Please try again.');
    }
});

// Handle adding games to the cart
app.post('/add-to-cart', isAuthenticated, (req, res) => {
    const gameId = req.body.gameId;

    if (!req.session.cart) {
        req.session.cart = [];
    }

    req.session.cart.push(gameId);
    res.redirect('/home');
});

// Handle removing games from the cart
app.post('/remove-from-cart', isAuthenticated, (req, res) => {
    const gameId = req.body.gameId;

    if (req.session.cart) {
        req.session.cart = req.session.cart.filter(id => id !== gameId);
    }

    res.redirect('/cart');
});

// Render the cart page
app.get('/cart', isAuthenticated, async (req, res) => {
    if (!req.session.cart) {
        return res.render('cart', { cartItems: [], totalAmount: 0 });
    }

    try {
        const cartItems = await Game.find({ _id: { $in: req.session.cart } });
        const totalAmount = cartItems.reduce((sum, game) => sum + game.price, 0);
        res.render('cart', { cartItems, totalAmount });
    } catch (error) {
        console.error('Error fetching cart items:', error);
        res.status(500).send('Error fetching cart items. Please try again.');
    }
});

// Handle placing an order
app.post('/place-order', isAuthenticated, async (req, res) => {
    const { cardNumber, expiryDate, cvv } = req.body;

    if (!req.session.cart) {
        return res.redirect('/cart');
    }

    try {
        const cartItems = await Game.find({ _id: { $in: req.session.cart } });
        const totalAmount = cartItems.reduce((sum, game) => sum + game.price, 0);

        const order = new Order({
            userId: req.session.user._id,
            games: req.session.cart,
            totalAmount,
            paymentDetails: { cardNumber, expiryDate, cvv }
        });

        await order.save();
        req.session.cart = [];
        
        const downloadLinks = cartItems.map(game => ({
            title: game.title,
            link: game.downloadLink
        }));
        res.render('order_confirmation', { downloadLinks });
    } catch (error) {
        console.error('Error placing order:', error);
        res.status(500).send('Error placing order. Please try again.');
    }
});

app.get('/', (req, res) => {
    res.render('index');
});

app.post('/', async (req, res) => {
    const { email, password } = req.body;

    try {
        const user = await User.findOne({ email, password });

        if (user) {
            req.session.user = user;
            res.redirect('/home');
        } else {
            res.redirect('/');
        }
    } catch (error) {
        console.error('Error finding user:', error);
    }
});

app.get('/logout', (req, res) => {
    req.session.destroy((err) => {
        if (err) {
            console.error('Error destroying session:', err);
        }
        res.redirect('/');
    });
});

app.get('/sign_up', (req, res) => {
    res.render('sign_up');
});

app.post('/sign_up', async (req, res) => {
    const { name, email, password } = req.body;
    try {
        const new_user = new User({ name, email, password });

        await new_user.save();
        res.redirect('/');
    } catch (error) {
        console.error('Error saving user:', error);
        res.status(500).send('Error saving user. Please try again.');
    }
});

function isAuthenticated(req, res, next) {
    if (req.session.user) {
        return next();
    }
    res.redirect('/');
}

app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});