/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:01:59 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/26 08:29:44 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>

# define READ_END 0 //STDIN
# define WRITE_END 1 //STDOUT
# define STDERR 2

typedef struct s_table
{
	int					*exit_code;
	int					num_pids;
	int					*pids;
	int					ipids;
	char				**envp;
}						t_table;

typedef struct s_command
{
	char				**args;
	char				*lim;
	int					fd_in;
	int					fd_out;
	int					here_doc;
	int					p[2];
	int					pprev;
	struct s_command	*next;
	t_table				*table;
	char				**token_quotes;
}						t_command;

typedef struct s_state
{
	int					n[2];
	int					i;
	int					sq_open;
	int					dq_open;
	char				*env_var;
	t_command			*cmd;
}						t_state;


// typedef struct s_sig
// {
//     int					exit_code;
//     int					received;
// } t_sig;

extern int				g_sig;

// =========================================================================
//                                PARSING
// =========================================================================

t_command				*fill_t_command(char *input, char **envp,
							int return_value);
t_command				*tokenize_input(char *input, char **envp,
							int return_value);
t_command				*initialize_t_command(t_table *table);
t_table					*initialize_t_main(char *line, char **envp,
							int *return_value);
t_state					*initialize_t_state(void);

void					allocate_t_table(t_command *, int count);
int						open_fct_check(char *file, int i);
void					free_t_command(t_command *cmd);
void					new_t_command(t_command *cmd, t_table *table);
void					add_line_to_history(const char *line);
int						find_fd_out(t_command *cmd);
int						helper_fd_out(t_command *cmd, char *file, int flags);
int						find_fd_in(t_command *cmd);
void					new_t_command(t_command *cmd, t_table *table);
void					free_t_command(t_command *cmd);
int						open_fct_check(char *file, int i);
int						ft_count_pipe(char *str);

// =========================================================================
//                                SIGNAUX
// =========================================================================

void					sig_int(int code);
void					sig_quit(int code);
void					handle_signal_interrupts(char *line);
char					*read_input(char **env);

// =========================================================================
//                                EXPAND
// =========================================================================

//------> t_command				*parse_pipeline_commands(char **tokens);
// / on utilise ca ?

char					*process_char(char *input, char *result, t_state *state,
							t_command *cmd);
char					*process_char_helper(const char *input, char **result,
							t_state *state);
char					*get_exit_code(int len, t_state *state);
char					*dollar_question_case(char *arg, t_state *state);
char					*get_env_var(char *input, const char *name, int len,
							t_state *state);
char					*get_prompt(void);
char					*make_expand(const char *input, t_state *state);
char					*helper_quotes(char *arg, char c, t_state *state);
char					*initialize_result(char *result, size_t result_size);
char					*expand_env_var(char *input, t_state *state);
char					*copy_quotes_to_arg(t_command *cmd, int *i);
void					copy_quote_strings(t_command *cmd, char *quotes[4096],
							t_state *state);
void					process_quotes(t_command *cmd, t_state *state);
void					print_command(t_command *cmd);
void					allocate_args(t_command *cmd);
void					process_token_arguments(char **tokens, t_command *cmd,
							int *j);
void					allocate_resources(char **result, t_state **state);
void					allocate_token_quotes(t_command *cmd, char *quotes[],
							t_state *state);
void					update_quotes(char ch, t_state *state, char *result,
							size_t result_size);
void					concat_exit_code(char *exit_c, size_t *ij,
							size_t total_size, t_state *state);
void					handle_state_quotes(t_state *state);
void					handle_double_quotes(char *arg, char **result,
							char *quotes[], t_state *state);
void					handle_single_quotes(char *arg, char *quotes[],
							t_state *state);
void					handle_dollar_sign(char *arg, char **result,
							char *quotes[], t_state *state);
void					handle_regular_char(char *arg, char *quotes[],
							t_state *state);
void					handle_quotes_and_expand(char *arg, char *result,
							t_command *cmd, t_state *state);
int						handle_env_var(const char *input, char *result,
							t_state *state, size_t result_size);
int						check_pair_quotes(t_command *cmd);
int						process_tokens(char **tokens, t_command *cmd, int *j);

int						expand_tokens(char **tokens, t_command *cmd,
							t_state *state);
int						split_and_process_tokens(t_command *cmd, char **tokens,
							t_table *table);
int						check_exp_ok(const char *input, int len,
							t_state *state);
int						check_expand_input(char *input);
// =========================================================================
//                                BUILTINS
// =========================================================================

void					bin_check(char *cmd);
int						check_cmd(t_command *cmd, char **envp);
char					*check_access(char **pathoche, char *cmd, int i);
int						check_path_in_env(char **envp);
int						check_line(char *line);

void					execute(t_command *cmd, char **envp);
int						execute_cmd(t_command *cmd, char **envp);

void					freetab(char **tab);
void					free_cmd(t_command *cmd);

int						here_doc(char *lim);

void					launch_exec(t_command *cmd, char **envp);
int						flunch(t_command *cmd, char **envp);
char					**exec_command(char *line, char **envp,
							int *return_value);
char					*find_path(t_command *cmd);
char					*path(char *cmd, char **envp);

int						wait_pids(t_command *cmd);

void					deal_out_pipe(t_command *cmd);
void					deal_in_pipe(t_command *cmd);

void					command_not_found(char *cmd);
void					print_command(t_command *cmd);

void					add_line_to_history(const char *line);
char					*get_prompt(void);
char					**get_env(char **envp);
char					*get_line(char **envp);

// =========================================================================
//                                BUILTINS
// =========================================================================

int						is_builtins(t_command *cmd);
void					command_not_found(char *cmd);
int						echo(t_command *cmd);
int						cd(char **tab);
int						pwd(void);
int						env(t_command *cmd);
int						unset(char ***envp, const char *var);
char					**ft_export(char *args, char **envp);
char					**get_env(char **envp);
int						here_main(char *lim);
#endif
