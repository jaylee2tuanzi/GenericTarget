![](doc/img/icon.svg)

# Generic Target

The Generic Target Toolbox can be used to run MATLAB/Simulink models (**>= R2020b**) on a target computer in realtime.
The target computer can be any computer that has at least one network interface and has a Linux operating system with
the PREEMPT_RT realtime patch installed. All Simulink blocks that allow code generation can be used. For low-level hardware
interfaces like network interfaces, the Generic Target Toolbox comes with its own blocks.

The directory structure of this repository is as follows.

| File / Directory   | Description                                                                                                  |
| :----------------- | :----------------------------------------------------------------------------------------------------------- |
| doc                | contains the documentation that can be created with [SimpleDoc](https://github.com/RobertDamerius/SimpleDoc) |
| lib                | contains the MATLAB Simulink library "GenericTarget" (**>= R2020b**)                                        |
| packages           | contains the MATLAB package "GT"                                                                             |
| readme.html        | forwards to the documentation                                                                                |
| install.m          | MATLAB script to install the Generic Target Toolbox                                                          |
| uninstall.m        | MATLAB script to uninstall the Generic Target Toolbox                                                        |
| LICENSE            | license information                                                                                          |
| README.md          | this file                                                                                                    |


> **Note**<br>
> The toolbox is currently in the first stage of development and testing.

### Revision History
| Date        | Version  | Description                                                                                               |
| :---------- | :------- | :-------------------------------------------------------------------------------------------------------- |
| 2021-01-26  | 1.0      | Initial release                                                                                           |


## How To Start
Look at the web-based documentation by opening the ``readme.html`` file with a browser. There you will find a more
detailed description of the Generic Target Toolbox as well as instructions on how to prepare the target computer and create
a first application.
