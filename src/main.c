/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:12 by vafleith          #+#    #+#             */
/*   Updated: 2024/09/05 15:55:51 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(t_env_list *env_list)
{
	int		seeking;
	char	**split_paths;

	seeking = -1;
	while (env_list)
	{
		seeking = ft_strncmp(env_list->name, "PATH", 4);
		if (!seeking)
			break ;
		env_list = env_list->next;
	}
	if (seeking)
		return (NULL);
	split_paths = ft_split(env_list->data + 5, ':');
	if (!split_paths)
		exit(1);
	return (split_paths);
}

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	t_token	*tokens;
	t_btree	*tree;
	char 	**paths;
	t_env	*envs;

	(void)argc;
	(void)argv;
	envs = init_envs(env);
	paths = get_paths(envs->env_list);
	// check malloc paths etc.
	while (1)
	{
		buffer = readline("$> ");
		add_history(buffer);
		if (!buffer)
			continue ;
		tokens = tokenize_cmdline(buffer);
		if (tokens == NULL)
		{
			continue;
			free(buffer);
		}
		tokens = parser(tokens);
		tree = create_ast(tokens);
		// print_structure(tree, 0);
		// btree_print_details(tree, 0);
		launch_pipeline(tree, envs, paths);
		// update_exit_status(envs->env_list, launch_pipeline(tree, envs, paths));
		if (tokens)
			ft_free_tokens(&tokens);
		if (tree)
			btree_free(tree);
		free(buffer);
	}
	envs->env_list = free_env_list(&(envs->env_list));
}

// if (ft_strlen(buffer) == ft_strlen("exit") && !ft_strncmp(buffer,
// 				"exit", 4))
// 		{
// 			free(buffer);
// 			exit(EXIT_SUCCESS);
// 		}


// void connect_commands(int prev_read_fd, const char* cmd) 
// {
//     int new_read_fd[2], 
	// int new_write_fd[2];
    
//     if (create_pipe(new_read_fd, new_write_fd) == -1) {
//         perror("Erreur création pipe");
//         exit(1);
//     }

//     dup2(prev_read_fd, new_write_fd[PIPE_READ]);
//     close(prev_read_fd);

//     dup2(new_read_fd[PIPE_READ], STDOUT_FILENO);
//     close(new_read_fd[PIPE_READ]);

//     printf("Exécutant : %s\n", cmd);
//     system(cmd);  // Note : Utilisation de system() pour simplifier l'exemple
//     close(new_write_fd[PIPE_WRITE]);
// }

// void traverse_ast(Node* root, int depth) {
//     if (root == NULL || depth > MAX_DEPTH) return;

//     if (root->left) {
//         traverse_ast(root->left, depth + 1);
//     }
//     connect_commands(STDOUT_FILENO, root->value);
//     if (root->right) {
//         traverse_ast(root->right, depth + 1);
//     }
// }

// void execute_pipeline(Node* root) {
//     traverse_ast(root, 0);
//     // Fermeture des descriptors ouverts
//     close(STDOUT_FILENO);
// }



    //  break;
            
    //     case NODE_PIPE:
    //         // Création d'un pipe
    //         int pipefd[2];
    //         if (pipe(pipefd) == -1) {
    //             perror("Erreur lors de la création du pipe");
    //             exit(EXIT_FAILURE);
    //         }
            
    //         // Connexion des deux sous-nœuds au pipe
    //         connect_node_to_pipe(node->left, pipefd[WRITE]);
    //         connect_node_to_pipe(node->right, pipefd[READ]);
            
    //         // Récurse sur les sous-nœuds
    //         connect_pipes(node->left);
    //         connect_pipes(node->right);
    //         break;


// d connect_node_to_pipe(Node* node, int pipe_fd) {
//     pid_t pid = fork();
    
//     if (pid == 0) {
//         // Dans le processus enfant
//         dup2(pipe_fd, STDOUT_FILENO);
//         close(pipe_fd);
        
//         // Exécution de la commande
//         execute_command(node->command);
//         _exit(EXIT_SUCCESS);
//     } else if (pid > 0) {
//         // Dans le processus parent
//         close(pipe_fd);
//         wait(NULL);
//     }

// nclude <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/wait.h>

// // Structure pour représenter un nœud de l'AST
// typedef struct Node 
// {
//     char* command;
//     struct Node* left;
//     struct Node* right;
// } Node;

// // Fonction pour créer un nouveau nœud AST
// Node* create_node(char* cmd) {
//     Node* node = malloc(sizeof(Node));
//     node->command = strdup(cmd);
//     node->left = NULL;
//     node->right = NULL;
//     return node;
// }

// // Fonction pour parcourir l'AST et exécuter les commandes
// void execute_ast(Node* root) {
//     if (root == NULL) return;

//     // Exécution de la commande courante
//     printf("Exécutant : %s\n", root->command);
//     system(root->command);

//     // Recursion sur le sous-arbre gauche
//     execute_ast(root->left);

//     // Création d'un pipe pour la connexion suivante
//     int fd[2];
//     if (pipe(fd) == -1) {
//         perror("Erreur création pipe");
//         exit(1);
//     }

//     // Processus enfant pour la commande droite
//     pid_t pid = fork();
//     if (pid == 0) {
//         // Dans le processus enfant
//         close(fd[0]);  // Fermer la lecture du pipe
//         dup2(fd[1], STDOUT_FILENO);  // Rediriger stdout vers le pipe
//         close(fd[1]);  // Fermer la sortie du pipe
//         execute_ast(root->right);
//         exit(0);
//     }
//     else if (pid > 0) {
//         // Dans le processus parent
//         close(fd[1]);  // Fermer la sortie du pipe
//         dup2(fd[0], STDIN_FILENO);  // Rediriger stdin vers le pipe
//         close(fd[0]);  // Fermer la lecture du pipe
//         wait(NULL);  // Attendre que le processus enfant se termine
//     }
//     else {
//         perror("Erreur fork");
//         exit(1);
//     }

//     // Recursion sur le sous-arbre droit
//     execute_ast(root->right);
// }

// int main() {
//     // Création d'un exemple d'AST
//     Node* root = create_node("ls -l");
//     root->left = create_node("grep keyword");
//     root->right = create_node("sort");

//     execute_ast(root);

//     return 0;
// }

// Explication du code

//     Nous définissons une structure Node pour représenter les nœuds de l'AST.

//     La fonction create_node permet de créer de nouveaux nœuds AST.

//     La fonction principale execute_ast parcourt récursivement l'AST :
//         Elle exécute la commande courante.
//         Elle continue la recursion sur le sous-arbre gauche.
//         Elle crée un pipe et lance un nouveau processus enfant pour la commande droite.
//         Elle attend que le processus enfant se termine avant de continuer avec le sous-arbre droit.

//     Dans le processus parent, nous configurons le pipe pour connecter la sortie de la commande précédente à l'entrée de la commande suivante.

//     Enfin, nous créons un exemple d'AST et appelons execute_ast pour démarrer l'exécution.

// Points clés à considérer

//     Cette implémentation est simplifiée et ne gère pas tous les cas possibles (par exemple, les erreurs de pipe).
//     Le système doit gérer correctement les erreurs et les signaux.
//     Pour des commandes complexes ou des pipelines plus longs, il faudrait optimiser davantage la gestion des processus et des pipes.
//     Il faut veiller à fermer correctement toutes les ressources (fils, descriptors de fichier) pour éviter les fuites de mémoire.

// Cette approche fournit une base solide pour comprendre comment connecter des commandes via des pipes en utilisant une structure AST en C. Vous pouvez l'étendre et la perfectionner selon vos besoins spécifiques.