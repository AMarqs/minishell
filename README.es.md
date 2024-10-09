# MINISHELL

42 proyect done by [@gonzalonao](https://github.com/gonzalonao) and me ([@AMarqs](https://github.com/AMarqs))


# Resumen

El objetivo de este proyecto es que crees un shell sencillo y el aprendezije más profundo procesos y file descriptors.


# Descripción

Tu shell deberá:
- Mostrar una entrada mientras espera un comando nuevo.
- Tener un historial funcional.
- Buscar y ejecutar el ejecutable correcto (basado en la variable PATH o mediante el uso de rutas relativas o absolutas).
- Evita utilizar más de una variable global para indicar la recepción de una señal. \
Piensa en lo que implica: Esta aproximación evita que tu gestor de señales acceda a tus estructuras de datos principales.

> [!WARNING]
> Esta variable global no puede proporcionar ninguna otra información o datos que el número de una señal recibida. Por lo tanto está prohibido utilizar estructuras de tipo “norm” en global.

- No interpretar comillas sin cerrar o caracteres especiales no especificados en el enunciado como \ (barra invertida) o ; (punto y coma).
- Gestionar que la ’ evite que el shell interprete los metacaracteres en la secuencia entrecomillada.
- Gestionar que la " evite que el shell interprete los metacaracteres en la secuencia entrecomillada exceptuando $ (signo de dólar).
- Implementar redirecciones:
  - "<" debe redirigir input.
  - ">" debe redirigir output.
  - "<<" debe recibir un delimitador, después leer del input de la fuente actual hasta que una línea que contenga solo el delimitador aparezca. Sin embargo, no necesita actualizar el historial.
  - ">>" debe redirigir el output en modo append.
- Implementar pipes (carácter |). El output de cada comando en la pipeline se
conecta a través de un pipe al input del siguiente comando.
- Gestionar las variables de entorno ($ seguidos de caracteres) que deberán ex-
pandirse a sus valores.
- Gestionar $?, que deberá expandirse al estado de salida del comando más reciente
ejecutado en la pipeline.
- Gestionar ctrl-C ctrl-D ctrl-\, que deberán funcionar como en bash.
- Cuando sea interactivo:
  - ctrl-C imprime una nueva entrada en una línea nueva.
  - ctrl-D termina el shell.
  - ctrl-\ no hace nada.
- Deberá implementar los built-ins:
  - echo con la opción -n.
  - cd solo con una ruta relativa o absoluta.
  - pwd sin opciones.
  - export sin opciones.
  - unset sin opciones.
  - env sin opciones o argumentos.
  - exit sin opciones.


# Guidelines

|   Nombre de programa  |           minishell         |
|:----------------------|:----------------------------|
|  Archivos a entregar  |      Makefile, *.h, *.c     |
|        Makefile       | NAME, all, clean, flean, re |
| Funciones autorizadas | readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs |
| Se permite usar libft |             Sí             |

> [!NOTE]
> La función readline puede producir algunos leaks que no necesitas arreglar. Eso no significa que tu código, sí, el código que has escrito, pueda producir leaks.
