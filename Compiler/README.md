This program is a simple compiler.

| Code Number # | Binary Code | Rule                     | Explanatiom |
|---------------|-------------|-------------------------------------------|-----------------------------------|
| 1             | 0000        |  STO `X`                         | Stores AC in register `X`           |
| 2             | 0001        |  PUT `X` `Y`                        | Storing `X` in Reg `Y`            |
| 3             | 0010        |  OUT (`Reg`)<br>OR<br>OUT (\` `string` \`)                        | No arg - Outputs AC<br>`Reg` input - Outputs values stored in register `Reg`<br>` string ` - Outputs `string` (Note that neither `can touch any of the text)            |
| 4             | 0011        |   ADD `X`                        |  AC + `X`           |
| 5             | 0100        |   SUB `X`                       | AC - `X`            |
| 6             | 0101        |   HALT                       |    Stops processing         |
| 7             | 0110        |  LOAD `X`                         |  Loading data from REG `X` into AC           |
| 8             | 0111        |  INPUT                        |  Takes Input from Keyboard & stores into AC           |
| 9             | 1000        |  CLEAR                        |   Clears all registers          |
| 10            | 1001        |  LOOP `REG`                        | Loops a number of times equal to the value stored in `REG`.            |
| 11            | 1010        |  LOOP_                        |   Denotes the end of a loop.          |
| 12            | 1011        |  ARY `X`                         | Creates an array (Vector) with the arbitrary name `X`           |
| 13            | 1110        |  LOOK `X` (`REG`)                        | Looks in Array X for the value in a register.<br>No input - Searches for the AC<br>Returns index on success, -1 on failure|
| 14            | 1101        | ADDARY REG `X` EndFragment | Adds the value stored in a register to the Array X            |

Comments can be made with the following format:

// `Comment text` ./

Please note that a space must be included between the text and the `./` symbol.
