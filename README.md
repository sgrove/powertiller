# PowerTiller

## Setup a OneGraph app:

Sign up at https://www.onegraph.com, create an app, and grab its id.

Open `src/config.re` and put the appId in there.

## Run this project:

```
npm install
npm start
# in another tab
npm run webpack
# in *another* tab if you don't want the chrome extension version
npx serve
```

Visit the npx url and it'll show you the related talks to the id set
in `index.re`


Back in https://www.onegraph.com/dashboard just add
`http://localhost:5000` to your app's CORS origins, and you should be
good to go.

![Adding extension origin to OneGraph app](imgs/onedash.png)
