In order to install the libraries for use in OpenCM using github, go to the "ROBOTIS/libraries/" folder and type in the following commands:

git init
git remote add -f origin https://github.com/Happyzippy/unicornRiders.git

git config core.sparseCheckout true

echo robots/<Library> > .git/info/sparse-checkout

git pull origin master