/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/**
 * @doc
 * @doc-symbol unix
 * @doc-kind module
 * @doc-module unix
 * @doc-order 0
 * @doc-since 11
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Starts and stops subprocesses with several optional pipes.
 * @description The Unix module brings system utilities. It currently contains heavier versions of popen and pclose, able to open several communication pipes with a subprocess.
 * @header lapin/unix.h
 *
 * @doc-lang fr
 * @brief Démarre et arrête des sous-processus avec plusieurs tubes optionnels.
 * @description Le module Unix apporte des utilitaires système. Il contient actuellement des versions plus lourdes de popen et pclose, capables d'ouvrir plusieurs tubes de communication avec un sous-processus.
 * @header lapin/unix.h
 */

#ifndef			__LAPIN_UNIX_H__
# define		__LAPIN_UNIX_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif
# include		<stdarg.h>
# include		<unistd.h>

/**
 * @doc
 * @doc-symbol t_bunny_subprocess
 * @doc-kind struct
 * @doc-module unix
 * @doc-order 100
 * @doc-since 11
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Describes the pid and communication channels of a subprocess.
 * @description t_bunny_subprocess has two purposes. Before calling bunny_popen, fill its input/output fields with true or false values to indicate which pipes must be created. After bunny_popen succeeds, the same fields contain the file descriptors associated with the created pipes, or -1 when the corresponding pipe was not requested.
 * @description The pid field is ignored as input and receives the forked process identifier as output. The custom pipe descriptors are left open in the child process, but their exact numeric values are assigned by the system and are not normalized to fixed descriptor numbers by LibLapin.
 * @field pid The pid of the forked process. This field is an output.
 * @field _stdin Set this field to true before bunny_popen to open a pipe connected to the standard input of the child process. After success, it contains the write side of this pipe in the parent process.
 * @field _stdout Set this field to true before bunny_popen to open a pipe connected to the standard output of the child process. After success, it contains the read side of this pipe in the parent process.
 * @field _stderr Set this field to true before bunny_popen to open a pipe connected to the standard error output of the child process. After success, it contains the read side of this pipe in the parent process.
 * @field custom_data_input Set this field to true before bunny_popen to open an extra custom pipe intended for data sent to the child process. After success, it contains the parent-side descriptor of this pipe.
 * @field custom_data_output Set this field to true before bunny_popen to open an extra custom pipe intended for data produced by the child process. After success, it contains the parent-side descriptor of this pipe.
 * @field custom_command_input Set this field to true before bunny_popen to open an extra custom pipe intended for commands sent to the child process. After success, it contains the parent-side descriptor of this pipe.
 * @field custom_command_output Set this field to true before bunny_popen to open an extra custom pipe intended for commands produced by the child process. After success, it contains the parent-side descriptor of this pipe.
 * @see bunny_popen
 * @see bunny_pclose
 *
 * @doc-lang fr
 * @brief Décrit le pid et les canaux de communication d'un sous-processus.
 * @description t_bunny_subprocess a deux usages. Avant d'appeler bunny_popen, remplissez ses champs d'entrée/sortie avec des valeurs true ou false pour indiquer quels tubes doivent être créés. Après le succès de bunny_popen, ces mêmes champs contiennent les descripteurs de fichiers associés aux tubes créés, ou -1 lorsque le tube correspondant n'a pas été demandé.
 * @description Le champ pid est ignoré en entrée et reçoit en sortie l'identifiant du processus fils. Les descripteurs des tubes personnalisés restent ouverts dans le processus fils, mais leurs valeurs numériques exactes sont assignées par le système et ne sont pas normalisées vers des numéros fixes par la LibLapin.
 * @field pid Le pid du processus fils. Ce champ est une sortie.
 * @field _stdin Mettez ce champ à true avant bunny_popen pour ouvrir un tube connecté à l'entrée standard du processus fils. En cas de succès, il contient le côté écriture de ce tube dans le processus parent.
 * @field _stdout Mettez ce champ à true avant bunny_popen pour ouvrir un tube connecté à la sortie standard du processus fils. En cas de succès, il contient le côté lecture de ce tube dans le processus parent.
 * @field _stderr Mettez ce champ à true avant bunny_popen pour ouvrir un tube connecté à la sortie d'erreur standard du processus fils. En cas de succès, il contient le côté lecture de ce tube dans le processus parent.
 * @field custom_data_input Mettez ce champ à true avant bunny_popen pour ouvrir un tube personnalisé supplémentaire destiné aux données envoyées au processus fils. En cas de succès, il contient le descripteur côté parent de ce tube.
 * @field custom_data_output Mettez ce champ à true avant bunny_popen pour ouvrir un tube personnalisé supplémentaire destiné aux données produites par le processus fils. En cas de succès, il contient le descripteur côté parent de ce tube.
 * @field custom_command_input Mettez ce champ à true avant bunny_popen pour ouvrir un tube personnalisé supplémentaire destiné aux commandes envoyées au processus fils. En cas de succès, il contient le descripteur côté parent de ce tube.
 * @field custom_command_output Mettez ce champ à true avant bunny_popen pour ouvrir un tube personnalisé supplémentaire destiné aux commandes produites par le processus fils. En cas de succès, il contient le descripteur côté parent de ce tube.
 * @see bunny_popen
 * @see bunny_pclose
 */
typedef struct		s_bunny_subprocess
{
  pid_t			pid;
  int			_stdin;
  int			_stdout;
  int			_stderr;
  int			custom_data_input;
  int			custom_data_output;
  int			custom_command_input;
  int			custom_command_output;
}			t_bunny_subprocess;

int			bunny_popen(t_bunny_subprocess		*subprocess,
				    char			**environment,
				    size_t			nbr_parameters,
				    ...);

int			bunny_pclose(t_bunny_subprocess		*subprocess,
				     int			delay_in_seconds);

#endif	/*		__LAPIN_UNIX_H__			*/
