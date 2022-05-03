syscall::open:entry
/execname == "student" || execname == "instructor" || execname == "hod" || execname == "admin"/
{
	printf("\n%s is opened by the user %d\n", copyinstr(arg0),uid);
}

syscall::open:return
/execname == "student" || execname == "instructor" || execname == "hod" || execname == "admin"/
{

	printf("\nOpen call returned the fd = %d\n", arg0);
}

syscall::read:entry
/execname == "student" || execname == "instructor" || execname == "hod" || execname == "admin"/
{
	printf("\nRead is called with the following arguments fd = %d, bufpointer = %d, size = %d\n", arg0, arg1, arg2);
}

syscall::read:return
/execname == "student" || execname == "instructor" || execname == "hod" || execname == "admin"/
{
	printf("\nRead returned the number of bytes read = %d\n", arg0);
}
syscall::write:entry
/execname == "student" || execname == "instructor" || execname == "hod" || execname == "admin"/
{
	printf("\nWrite is called with the following arguments fd = %d, bufpointer = %d, size = %d\n", arg0, arg1, arg2);
}

syscall::write:return
/execname == "student" || execname == "instructor" || execname == "hod" || execname == "admin"/
{
	printf("\nWrite returned the number of bytes written = %d\n", arg0);
}

syscall::close:entry
/execname == "student" || execname == "instructor" || execname == "hod" || execname == "admin"/
{
	printf("\nClose is called with the following fd = %d\n", arg0);
}

syscall::close:return
/execname == "student" || execname == "instructor" || execname == "hod" || execname == "admin"/
{
	printf("\nClose returned with the following: %d\n", arg0);
}

proc:::exec
{
	printf("\nNew process is called by user %d\n", uid);
}

proc:::exit
{
	printf("\n%s process is exited with return value = %d\n", execname, arg0);
}

proc:::exec-success
{
	printf("\n%s process is successfully started\n",execname);
}

proc:::exec-failure
{
	printf("\nthe process is failed to start\n");
}
