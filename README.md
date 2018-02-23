# HaySense

A Particle library for interfacing with [our](https://github.com/dean-lab-group) haybale environmental sensor feather.


**This library depends on** [FreqPeriodCounter](https://github.com/elec3647/FreqPeriodCounter) (follow link to clone)

## Usage

Connect your hardware, add the HaySense library to your project and follow this simple example:

```
#include "HaySense.h"
HaySense haySense;

void setup() {
  haySense.begin();
}

void loop() {
  haySense.process();
}
```
Ensure that [FreqPeriodCounter](https://github.com/elec3647/FreqPeriodCounter) is also in your build path.

See the [examples](examples) folder for more details on using this library.

## Documentation
The sensors output pretty noisy data so its best to take a [moving average](https://en.wikipedia.org/wiki/Moving_average) of several samples.

## Contributing

Here's how you can make changes to this library and eventually contribute those changes back.

To get started, [clone the library from GitHub to your local machine](https://help.github.com/articles/cloning-a-repository/).

Change the name of the library in `library.properties` to something different. You can add your name at then end.

Modify the sources in <src> and <examples> with the new behavior.

To compile an example, use `particle compile examples/usage` command in [Particle CLI](https://docs.particle.io/guide/tools-and-features/cli#update-your-device-remotely) or use our [Desktop IDE](https://docs.particle.io/guide/tools-and-features/dev/#compiling-code).

After your changes are done you can upload them with `particle library upload` or `Upload` command in the IDE. This will create a private (only visible by you) library that you can use in other projects. Do `particle library add HaySense_myname` to add the library to a project on your machine or add the HaySense_myname library to a project on the Web IDE or Desktop IDE.

At this point, you can create a [GitHub pull request](https://help.github.com/articles/about-pull-requests/) with your changes to the original library. 

If you wish to make your library public, use `particle library publish` or `Publish` command.

## LICENSE
See [LICENSE.md](LICENSE.md) for details.
