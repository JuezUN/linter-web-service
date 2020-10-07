# UNCode linter service

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/302761f067f54331b2fa5865a8ed15e5)][codacy_url]
[![License](https://img.shields.io/github/license/JuezUN/linter-web-service?style=plastic)][license_url]
[![Contributors](https://img.shields.io/github/contributors/JuezUN/linter-web-service?style=plastic)][contributors_url]
[![GitHub issues](https://img.shields.io/github/issues/JuezUN/linter-web-service?style=plastic)][issues_url]
[![CLA assistant](https://cla-assistant.io/readme/badge/JuezUN/linter-web-service)][cla_url]
[![Gitter](https://badges.gitter.im/uncode-unal/community.svg)][gitter_url]

This code creates a linting service for UNCode, via a container which is in [Docker Hub][docker_hub_uncode] in the
 repository [unjudge/linter-web-service][unjudge/linter-web-service_url]. 

## Getting started

### Dependencies

- Ruby 2.3
- [Sinatra][sinatra_url]
- [Coala bears][coala_url]
 
Currently, the linter supports C/C++, Java and Python3.6+.

### Install 

#### Using docker
This is recommended option, because all the dependencies are already installed, as coala requires other additional
 dependencies that might be a pain.

##### Build container

In case new changes where added, run next command to update the container with the new changes:

```bash
docker build -t unjudge/linter-web-service ./
```

##### Run container

To start the container, run next command:

```bash
docker run -d -p 4567:4567 unjudge/linter-web-service
```

You can either do this with `docker-compose`.

#### Linux

Some initial dependencies are required first, please run next commands:

```bash
sudo apt-get install -y ruby
sudo gem install bundler #bundler
sudo apt-get install -y python3-pip
pip3 install coala-bears #coala, better if you use a virtualenv
```

We recommend you use a [python virtual environment][virtual_env_url] to avoid issues with other dependencies.
 Additionally, coala requires some other dependencies to correctly lint the supported languages, such as Java and GCC,
 check the `Dockerfile` to see the installed and required dependencies.

To start the linter service, run:

```bash
bundle install #this will install all ruby dependencies
ruby src/linter-webapp.rb
```

This will start the service in port `4567`.

### Possible problems

- Please make sure that you have installed all the executables dependencies for coala.

## Documentation

For additional documentation about UNCode, please refer to the [Wiki][uncode_wiki_url].

## Roadmap

See the [UNCode GitHub Project][project_url] for a list of proposed features for UNCode, known issues and how they are
 being tackled.

## Contributing

Go to [CONTRIBUTING][contributing_url] to see the guidelines and how to start contributing to UNCode.

## License

Distributed under the AGPL-3.0 License. See [LICENSE][license_url] for more information.

## Contact

In case of technical questions, please use the [gitter communication channel][gitter_url].

In case you want to host your course on our deployment, email us on: <uncode_fibog@unal.edu.co>

UNCode: <https://uncode.unal.edu.co>

Project page: <https://juezun.github.io/UNCode_page/>

[license_url]: https://github.com/JuezUN/linter-web-service/blob/master/LICENSE
[gitter_url]:https://gitter.im/uncode-unal/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge
[uncode_wiki_url]: https://github.com/JuezUN/INGInious/wiki
[project_url]: https://github.com/orgs/JuezUN/projects/3
[contributing_url]: https://github.com/JuezUN/linter-web-service/blob/master/CONTRIBUTING.md
[coala_url]: https://coala.io
[codacy_url]: https://www.codacy.com/gh/JuezUN/linter-web-service/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=JuezUN/linter-web-service&amp;utm_campaign=Badge_Grade
[docker_hub_uncode]: https://hub.docker.com/r/unjudge
[unjudge/linter-web-service_url]: https://hub.docker.com/r/unjudge/linter-web-service
[sinatra_url]: http://sinatrarb.com/
[virtual_env_url]: http://python-guide-pt-br.readthedocs.io/en/latest/dev/virtualenvs/
[contributors_url]: https://github.com/JuezUN/INGInious-containers/graphs/contributors
[issues_url]: https://github.com/JuezUN/INGInious-containers/issues
[cla_url]: https://cla-assistant.io/JuezUN/INGInious-containers
