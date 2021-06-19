# minishell

### Keyboard handling

##### Mandatory
1. Normal input such as alphabets and numbers 
2. Arrow up and arrow down for browsing history
3. Ctrl-D, Ctrl-C, Ctrl-\ send signals as in bash

##### Bonus
1. Backspace and delete work as in bash
2. Arrow left and arrow right work as in bash (to move the cursor)
3. Ctrl-L works as in bash
4. Home and end to move the cursor to the beginning or the back of the line respectively

### Parsing

##### Mandatory
1. Quotes (') and double quotes (") work as in bash except for multiline commands
2. Pipe ('|') works as in bash
3. Redirections ('<', '>', '<<'. '>>') work as in bash
4. Dollar sign ('$') looks for the corresponding environment variable or "$?"

##### Bonus
1. Backslash ('\') works as in bash except for multiline commands
2. Semicolon (';') works as in bash
3. Asterisk ('*') works as in bash (not only in current working direcotry)
4. Tilde ('~') works as in bash except when $HOME is not set (A forbidden function is necessary to simulate this situation).

### Builtins (xli 交給你了)

### Other features
1. Change text color and change prompt color
##### supported colors : 
BLACK, WHITE, RED, GREEN, YELLOW, PURPLE, BLUE, CYAN
##### usage :
To change text color, simply type one of the "supported colors" in capital letters.

![intro1](https://user-images.githubusercontent.com/70040774/122655992-3535a480-d157-11eb-84db-2228bc7b496d.png)


To change prompt color, type P_"supported color" in capital letters.

![intro2](https://user-images.githubusercontent.com/70040774/122655999-4383c080-d157-11eb-8ff9-e01585e36018.png)
