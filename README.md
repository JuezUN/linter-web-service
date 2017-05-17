# JuezUN lint webservice

This is the code that makes up the service of linting in the JuezUN platform. In order to run a full-feature instance you would need to install the [coala linter](https://coala.io) and make sure that the console from where you launch the server has access to the command 'coala'

### Development

#### Dependencies
```bash
sudo apt-get install -y ruby
sudo gem install bundler #bundler (like a pip for ruby)
sudo apt-get install -y python3-pip #pip3
pip3 install coala-bears #coala, better if you use a virtualenv
```
[virtualenv info](http://python-guide-pt-br.readthedocs.io/en/latest/dev/virtualenvs/)

#### Running the server
```bash
bundle install #this will install all the dependencies
ruby src/linter-webapp.rb
```

#### Running tests
```bash
bundle exec rspec path/to/your/test.rb
```
### Issues
#### The linter is not available
Plase make sure that you have installed all the executables dependencies for coala. (This is a pain) because coala calls linters installed in the environment
