which -s brew
if [[ $? != 0 ]] ; then
	rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update && brew install readline
else
	brew update && brew install readline
fi
