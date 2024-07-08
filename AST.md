# Structure of parsing

![image](https://github.com/valentinefleith/Minishell/assets/125041345/c14b8707-fa6b-4781-b216-aaa53d701681)

![image](https://github.com/valentinefleith/Minishell/assets/125041345/dcd60f26-c572-4c1e-b41d-831f4f14b541)

![image](https://github.com/valentinefleith/Minishell/assets/125041345/4a10f20c-651d-4db1-9174-3da5793cb72e)

![image](https://github.com/valentinefleith/Minishell/assets/125041345/d19bfdae-b738-4a0b-a3f2-c0fe44407105)


### AST vs parse trees

![image](https://github.com/valentinefleith/Minishell/assets/125041345/9856b4d1-f6f8-4e34-937c-be2035359f6e)

![image](https://github.com/valentinefleith/Minishell/assets/125041345/7293b05e-eecb-496c-81d1-49549352d626)

As you can see from the picture above, the AST captures the essence of the input while being smaller.

Here are the main differences between ASTs and Parse trees:

  - ASTs uses operators/operations as root and interior nodes and it uses operands as their children.
 - ASTs do not use interior nodes to represent a grammar rule, unlike the parse tree does.
- ASTs don’t represent every detail from the real syntax (that’s why they’re called abstract) - no rule nodes and no parentheses, for example.
- ASTs are dense compared to a parse tree for the same language construct.

So, what is an abstract syntax tree? An abstract syntax tree (AST) is a tree that represents the abstract syntactic structure of a language construct where each interior node and the root node represents an operator, and the children of the node represent the operands of that operator.

I’ve already mentioned that ASTs are more compact than parse trees. 

# Shell grammar and example of trees

![image](https://github.com/valentinefleith/Minishell/assets/125041345/0ad8331a-b1b1-4fb7-a70a-291800cb574e)

![image](https://github.com/valentinefleith/Minishell/assets/125041345/abb1dda8-e4bc-4669-b240-39c2eb32068b)

Simple version of grammar:
```
pipe_sequence    : simple_command
                 | pipe_sequence '|' simple_command
                 ;
cmd_suffix       : cmd_word
                 | cmd_word cmd_word
                 ;
simple_command   : cmd_name
                 | cmd_name cmd_suffix
                 ;
cmd_name         : WORD                   
                 ;
cmd_word         : WORD
                 ;
```

# Binary trees
How do you navigate the tree to properly evaluate the expression represented by that tree? You do that by using a postorder traversal - a special case of depth-first traversal - which starts at the root node and recursively visits the children of each node from left to right. The postorder traversal visits nodes as far away from the root as fast as it can.

Here is a pseudo code for the postorder traversal where <<postorder actions>> is a placeholder for actions like addition, subtraction, multiplication, or division for a BinOp node or a simpler action like returning the integer value of a Num node:
![image](https://github.com/valentinefleith/Minishell/assets/125041345/cab34f9a-f2e7-42c0-b37c-77c3688fdf3e)

For the sake of completeness, I’ll mention that there are three types of depth-first traversal: preorder traversal, inorder traversal, and postorder traversal. The name of the traversal method comes from the place where you put actions in the visitation code:


![image](https://github.com/valentinefleith/Minishell/assets/125041345/79ca36c8-e685-47f6-bffe-016ac8a80561)

