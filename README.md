# EZGraphLib

EZGraphLib is an open-source [PROS](https://pros.cs.purdue.edu/) library that simplifies graphing data on the [v5 brain](https://www.vexrobotics.com/276-4810.html). 

<img src="IMG_3933.png" width=100>

## Installation

Use the [PROS CLI](https://github.com/purduesigbots/pros-cli/releases) to install EZGraphLib. If you installed PROS correctly, you should already have the PROS CLI. 

1. Download ``EZGraphLib@LATEST_VERSION.zip`` (found [here](https://github.com/Yessir120/EZGraphLib/releases)) at the root of your project
2. Run ``pros conductor fetch EZGraphLib@LATEST_VERSION.zip`` at the root of your project
3. Run ``pros conductor apply EZGraphLib`` at the root of your project
4. Add ``#include "EZGraphLib/Grapher.hpp"`` to your header file

## Usage

```python
import foobar

# returns 'words'
foobar.pluralize('word')

# returns 'geese'
foobar.pluralize('goose')

# returns 'phenomenon'
foobar.singularize('phenomena')
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[GPL-3.0](https://choosealicense.com/licenses/gpl-3.0/)
