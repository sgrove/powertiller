const path = require('path');

module.exports = {
    entry: './src/index.bs.js',
    output: {
        path: path.join(__dirname, "build"),
        filename: 'index.js',
    },
    module: {
        rules: [{
            test: /\.less$/,
            use: ["style-loader", "css-loader", "less-loader"]
        }]
    }
};
