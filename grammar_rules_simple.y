Grammar
    0 $accept → program $end

    1 program → command

    2 command → cmd_name cmd_suffix
    3         | cmd_name

    4 cmd_name → WORD

    5 cmd_suffix → WORD
    6            | cmd_suffix WORD
<SNIP>
Automaton
State 0

    0 $accept → • program $end
    1 program → • command
    2 command → • cmd_name cmd_suffix
    3         | • cmd_name
    4 cmd_name → • WORD

    WORD  shift, and go to state 1

    program   go to state 2
    command   go to state 3
    cmd_name  go to state 4
State 1

    4 cmd_name → WORD •

    $default  reduce using rule 4 (cmd_name)
State 2

    0 $accept → program • $end

    $end  shift, and go to state 5
State 3

    1 program → command •

    $default  reduce using rule 1 (program)
State 4

    2 command → cmd_name • cmd_suffix
    3         | cmd_name •  [$end]
    5 cmd_suffix → • WORD
    6            | • cmd_suffix WORD

    WORD  shift, and go to state 6

    $default  reduce using rule 3 (command)

    cmd_suffix  go to state 7
State 5

    0 $accept → program $end •

    $default  accept
State 6

    5 cmd_suffix → WORD •

    $default  reduce using rule 5 (cmd_suffix)
State 7

    2 command → cmd_name cmd_suffix •  [$end]
    6 cmd_suffix → cmd_suffix • WORD

    WORD  shift, and go to state 8

    $default  reduce using rule 2 (command)
State 8

    6 cmd_suffix → cmd_suffix WORD •

    $default  reduce using rule 6 (cmd_suffix)
