/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/13 22:38:43 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ctrl	*get_control(void)
{
	static t_ctrl	control;

	return (&control);
}

int	main(int argc, char **argv, char **env)
{
	t_ctrl	*control;

	(void)argc;
	control = get_control();
	control->env = parse_env(env);
	update_env(argv, NULL, NULL);
	while (1)
		prompt_user("msh:> ");
	exit_program(0);
}


/*
Test   1: ✅ echo hello world 
ok
Test   2: ✅ echo "hello world" 
ok
Test   3: ✅ echo 'hello world' 
ok
Test   4: ✅ echo hello'world' 
ok
Test   5: ✅ echo hello""world 
ok
Test   6: ✅ echo '' 
ok
Test   7: ✅ echo "$PWD" 
ok
Test   8: ✅ echo '$PWD' 
ok
Test   9: ✅ echo "aspas ->'" 
ok
Test  10: ✅ echo "aspas -> ' " 
ok
Test  11: ✅ echo 'aspas ->"' 
ok
Test  12: ✅ echo 'aspas -> " ' 
ok
Test  13: ✅ echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<" 
ok
Test  14: ✅ echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<' 
ok
Test  15: ✅ echo "exit_code ->$? user ->$USER home -> $HOME" 
ok
Test  16: ✅ echo 'exit_code ->$? user ->$USER home -> $HOME' 
ok
Test  17: ✅ echo "$" 
ok
Test  18: ✅ echo '$'
ok
Test  19: ✅ echo $ 
ok
Test  20: ✅ echo $? 
ok
Test  21: ✅ echo $?HELLO 
ok
Test  22: ✅ pwd 
ok
Test  23: ✅ pwd oi 
ok
Test  24: ✅ export hello 
ok
Test  25: ✅ export HELLO=123 
ok
Test  26: ✅ export A- 
ok
Test  27: ✅ export HELLO=123 A 
ok
Test  28: ✅ export HELLO="123 A-" 
ok
Test  29: ✅ export hello world 
ok
Test  30: ✅ export HELLO-=123 
ok
Test  31: ✅ export = 
ok
Test  32: ✅ export 123 
ok
Test  33: ✅ unset 
ok
Test  34: ✅ unset HELLO 
ok
Test  35: ✅ unset HELLO1 HELLO2 
ok
Test  36: ✅ unset HOME 
ok
Test  37: ✅ unset PATH 
ok
Test  38: ✅ unset SHELL 
ok
Test  39: ✅ cd $PWD 
ok
Test  40: ✅ cd $PWD hi 
ok
Test  41: ✅ cd 123123 
ok
Test  42: ✅ exit 123 
ok
Test  43: ✅ exit 298 
ok
Test  44: ✅ exit +100 
ok
Test  45: ✅ exit "+100" 
ok
Test  46: ✅ exit +"100" 
ok
Test  47: ✅ exit -100 
ok
Test  48: ✅ exit "-100" 
ok
Test  49: ✅ exit -"100" 
ok
Test  50: ✅ exit hello 
ok
Test  51: ✅ exit 42 world 
ok
Test  52: ✅  
———————————— pipes
Test  53: ✅ env | sort | grep -v SHLVL | grep -v ^_ 
ok
Test  54: ✅ cat ./test_files/infile_big | grep oi 
ok
Test  55: ✅ cat minishell.h | grep ");"$ 
ok
Test  56: ✅ export GHOST=123 | env | grep GHOST 
ok
———————————— redirects
Test  57: ✅ grep hi <./test_files/infile 
ok
Test  58: ✅ grep hi "<infile" <         ./test_files/infile 
ok
Test  *59: ✅ echo hi < ./test_files/infile bye bye 
ok
Test  60: ✅ grep hi <./test_files/infile_big <./test_files/infile 
ok
Test  61: ✅ echo <"./test_files/infile" "bonjour       42" 
ok
Test  62: ✅ cat <"./test_files/file name with spaces" 
ok
Test  63: ✅ cat <./test_files/infile_big ./test_files/infile 
ok
Test  64: ✅ cat <"1""2""3""4""5" 
ok
Test  65: ✅ echo <"./test_files/infile" <missing <"./test_files/infile" 
ok
Test  66: ✅ echo <missing <"./test_files/infile" <missing 
ok
Test  67: ✅ cat <"./test_files/infile" 
ok
Test  68: ✅ echo <"./test_files/infile_big" | cat <"./test_files/infile"  
nok (SIGPIPE)
Test  69: ✅ echo <"./test_files/infile_big" | cat "./test_files/infile" 
ok
Test  70: ✅ echo <"./test_files/infile_big" | echo <"./test_files/infile" 
nok (SIGPIPE)
Test  71: ✅ echo hi | cat <"./test_files/infile" 
nok (SIGPIPE)
Test  72: ✅ echo hi | cat "./test_files/infile" 
ok
Test  73: ✅⚠️  cat <"./test_files/infile" | echo hi 
mini error = ()
bash error = ( Broken pipe)
ok
Test  74: ✅ cat <"./test_files/infile" | grep hello 
ok
Test  75: ✅⚠️  cat <"./test_files/infile_big" | echo hi 
mini error = ()
bash error = ( Broken pipe)
nok (cat open)
Test  76: ✅ cat <missing 
ok
Test  77: ✅ cat <missing | cat 
ok
Test  78: ✅ cat <missing | echo oi 
ok
Test  79: ✅ cat <missing | cat <"./test_files/infile" 
ok
Test  80: ✅ echo <123 <456 hi | echo 42 
ok
Test  81: ✅ ls >./outfiles/outfile01 
Test  82: ✅ ls >         ./outfiles/outfile01 
Test  83: ✅ echo hi >         ./outfiles/outfile01 bye 
Test  84: ✅ ls >./outfiles/outfile01 >./outfiles/outfile02 
Test  85: ✅ ls >./outfiles/outfile01 >./test_files/invalid_permission 
Test  86: ✅ ls >"./outfiles/outfile with spaces" 
Test  87: ✅ ls >"./outfiles/outfile""1""2""3""4""5" 
Test  88: ✅ ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02" 
Test  89: ✅ ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission 
Test  90: ✅ cat <"./test_files/infile" >"./outfiles/outfile01" 
Test  91: ✅ echo hi >./outfiles/outfile01 | echo bye 
Test  92: ✅ echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye 
Test  93: ✅ echo hi | echo >./outfiles/outfile01 bye 
Test  94: ✅ echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02 
Test  95: ✅ echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02 
Test  96: ✅ echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye 
Test  97: ✅ echo hi >./test_files/invalid_permission | echo bye 
Test  98: ✅ echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye 
Test  99: ✅ echo hi | echo bye >./test_files/invalid_permission 
Test 100: ✅ echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission 
Test 101: ✅ echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01 
Test 102: ✅ cat <"./test_files/infile" >./test_files/invalid_permission 
Test 103: ✅ cat >./test_files/invalid_permission <"./test_files/infile" 
Test 104: ✅ cat <missing >./outfiles/outfile01 
Test 105: ✅ cat >./outfiles/outfile01 <missing 
Test 106: ✅ cat <missing >./test_files/invalid_permission 
Test 107: ✅ cat >./test_files/invalid_permission <missing 
Test 108: ✅ cat >./outfiles/outfile01 <missing >./test_files/invalid_permission 
Test 109: ✅ ls >>./outfiles/outfile01 
Test 110: ✅ ls >>      ./outfiles/outfile01 
Test 111: ✅ ls >>./outfiles/outfile01 >./outfiles/outfile01 
Test 112: ✅ ls >./outfiles/outfile01 >>./outfiles/outfile01 
Test 113: ✅ ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02 
Test 114: ✅ ls >>./outfiles/outfile01 >>./outfiles/outfile02 
Test 115: ✅ ls >>./test_files/invalid_permission 
Test 116: ✅ ls >>./test_files/invalid_permission >>./outfiles/outfile01 
Test 117: ✅ ls >>./outfiles/outfile01 >>./test_files/invalid_permission 
Test 118: ✅ ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02 
Test 119: ✅ ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02 
Test 120: ✅ ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing 
Test 121: ✅ echo hi >>./outfiles/outfile01 | echo bye 
Test 122: ✅ echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye 
Test 123: ✅ echo hi | echo >>./outfiles/outfile01 bye 
Test 124: ✅ echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02 
Test 125: ✅ echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02 
Test 126: ✅ echo hi >>./test_files/invalid_permission | echo bye 
Test 127: ✅ echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye 
Test 128: ✅ echo hi | echo bye >>./test_files/invalid_permission 
Test 129: ✅ echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission 
Test 130: ✅ cat <minishell.h>./outfiles/outfile 
Test 131: ✅ cat <minishell.h|ls 
———————————— extras
Test 132: ✅  
Test 133: ✅⚠️  $PWD 
mini error = ( command not found)
bash error = ( Is a directory)
Test 134: ✅ $EMPTY 
Test 135: ✅ $EMPTY echo hi 
Test 136: ✅⚠️  ./test_files/invalid_permission 
mini error = ( command not found)
bash error = ( Permission denied)
Test 137: ✅⚠️  ./missing.out 
mini error = ( command not found)
bash error = ( No such file or directory)
Test 138: ✅ missing.out 
Test 139: ✅ "aaa" 
Test 140: ✅ test_files 
Test 141: ✅⚠️  ./test_files 
mini error = ( command not found)
bash error = ( Is a directory)
Test 142: ✅⚠️  /test_files 
mini error = ( command not found)
bash error = ( No such file or directory)
Test 143: ✅ minishell.h 
Test 144: ✅ $ 
Test 145: ✅ $? 
Test 146: ✅ README.md 

SHELL SESSION_MANAGER COLORTERM HISTCONTROL XDG_MENU_PREFIX HISTSIZE HOSTNAME MAKE_TERMOUT SSH_AUTH_SOCK XMODIFIERS DESKTOP_SESSION EDITOR PWD LOGNAME XDG_SESSION_DESKTOP XDG_SESSION_TYPE SYSTEMD_EXEC_PID XAUTHORITY GDM_LANG HOME USERNAME LANG LS_COLORS XDG_CURRENT_DESKTOP VTE_VERSION WAYLAND_DISPLAY GNOME_TERMINAL_SCREEN MFLAGS MOZ_GMP_PATH GNOME_SETUP_DISPLAY XDG_SESSION_CLASS MAKEFLAGS TERM LESSOPEN USER MAKE_TERMERR GNOME_TERMINAL_SERVICE DISPLAY SHLVL MAKELEVEL ANDROID_SDK_ROOT QT_IM_MODULE XDG_RUNTIME_DIR DEBUGINFOD_URLS XDG_DATA_DIRS PATH GDMSESSION DBUS_SESSION_BUS_ADDRESS MAIL OLDPWD LD_PRELOAD _
*/
