Serial Slider
=====

Arduino Leonardo-based CHUNITHM ground slider for segatools.

By ilufang.

Overview
-----

This project is dedicated to the PC setup of CHUNITHM, unlike my previous
project ground-slider which is designed to be a potentially general-purpose
rhythm game controller. The ground-slider project is divided into sensor module
and game logic module, but this project is divided into the main device and
side device. The main device part directly talks to the game process through
COM1, bypassing the slider hooks in segatools. The side device sends keystrokes,
which is processed by the jvs hooks in segatools (ioctls were involved which
require driver software on the host to work, so just use segatools for
convenience).

Usage
-----

The main device creates a serial port. Please use device manager to assign this
port to `COM1` as CHUNITHM expects the main device on that port number. You will
also need to disable the segatools slider hook by setting `enabled` to 0 under
the `[slider]` section in segatools.ini.

The side device sends keystrokes. By default the 6 IR rays, when broken, sends
the numbers 4 through 9, with 4 being the lowest ray and 9 being the highest
ray. You will need a modified segatools either from my ilufang-dev branch, or
possibly a future official version as these changes are not yet merged at the
time of writing. You will need to configure the `[ir]` section in segatools.ini.

Building
-----

You need the following libraries in your Arduino libraries folder in order to
build:

* [NicoHood/HID @ 2.5.0](https://github.com/NicoHood/HID/releases/download/2.5.0/HID-2.5.0.tar.xz) ([repo](https://github.com/NicoHood/HID))
* [FastLED @ 3.2.10](https://github.com/FastLED/FastLED/archive/3.2.10.tar.gz) ([repo](https://github.com/FastLED/FastLED))

Newer versions of the libraries may also work, but have not been tested. (Let me
know if you tried)

License
-----

Unlicensed.

While I am personally allowing you to reuse and redistribute this project as you
would to any open-source project shared under a permissive license, I am not
specifying legal license terms for such permission.

The creation of this code takes advantage of information published in the
segatools project, which was not licensed. The project may require proprietary
software, and the project neither includes nor provides such software.

Due to the nature of tools like this project, I request that you do not share
this with the general public (e.g., do not fork to GitHub). However, please do
make it freely available to communities that may find this project useful. I do
not endorse or sponsor any activity related to the project.

The MPR121 code is a heavily modified version of the Adafruit MPR121 library. It
was originally licensed under modified terms of MIT or BSD. I licensed my
modifications under MIT. See the files for the license terms.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
WITH THE SOFTWARE.

