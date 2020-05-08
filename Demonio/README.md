para compilar hay que crear el objeto .o de copia.c y sincro.c. y luego el ejecutable usando los dos .o
 gcc -c copia.c
 gcc -c  sincro.c

gcc sincro.o copia.o -o sincro


Daemons:
Un daemon tiene dos requisitos generales: debe ejecutarse como un hijo de init y no debe estar conectado a un terminal.
En general, un programa realiza los siguientes pasos para convertirse en un daemon:
1. Call fork(). This creates a new process, which will become the daemon.
2. In the parent, call exit(). This ensures that the original parent (the daemon’s grandparent) is satisfied that its child terminated, that the daemon’s parent is no longer running, and that the daemon is not a process group leader. This last point is a requirement for the successful completion of the next step.
3. Call setsid(), giving the daemon a new process group and session, both of which have it as leader. This also ensures that the process has no associated controlling terminal (as the process just created a new session and will not assign one).
4. Change the working directory to the root directory via chdir(). This is done be‐ cause the inherited working directory can be anywhere on the filesystem. Daemons tend to run for the duration of the system’s uptime, and you don’t want to keep some random directory open and thus prevent an administrator from unmounting the filesystem containing that directory.
5. Close all file descriptors. You do not want to inherit open file descriptors, and, unaware, hold them open.
6. Open file descriptors 0, 1, and 2 (standard in, standard out, and standard error) and redirect them to /dev/null.

Para su funcionamiento copiar sinc.conf en home/<user>

listar daemons: 
ps -eo 'tty,pid,comm' | grep ^?

ver daemons :
pgrep inotify

ver eventos :
sudo cat /var/log/user.log
