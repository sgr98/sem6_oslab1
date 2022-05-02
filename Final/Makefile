student: ./UI/content.cpp ./UI/editor.cpp ./Main/student.cpp ./Student/student.cpp ./Instructor/instructor_marks_list.cpp
	g++ ./UI/content.cpp ./UI/editor.cpp ./Main/student.cpp ./Student/student.cpp ./Instructor/instructor_marks_list.cpp -o student
	setfacl -m u::--- student
	setfacl -m g::--x student
	setfacl -m g:students:--x student
	setfacl -m o::--- student
	sudo chown root:studentsexecute student
	sudo chmod g+s student

instructor: ./UI/content.cpp ./UI/editor.cpp ./Main/instructor.cpp ./Student/student.cpp ./Instructor/instructor_marks_list.cpp
	g++ ./UI/content.cpp ./UI/editor.cpp ./Main/instructor.cpp ./Student/student.cpp ./Instructor/instructor_marks_list.cpp -o instructor
	setfacl -m u::--- instructor
	setfacl -m g::--x instructor
	setfacl -m g:Faculty:--x instructor
	setfacl -m o::--- instructor
	sudo chown root:facultyexecute instructor
	sudo chmod g+s instructor

hod: ./UI/content.cpp ./UI/editor.cpp ./Main/hod.cpp ./Hod/hod.cpp ./Instructor/instructor_marks_list.cpp
	g++ ./UI/content.cpp ./UI/editor.cpp ./Main/hod.cpp ./Hod/hod.cpp ./Instructor/instructor_marks_list.cpp -o hod

admin: ./UI/content.cpp ./UI/editor.cpp ./Main/admin.cpp ./Admin/adminHelper.cpp
	g++ ./UI/content.cpp ./UI/editor.cpp ./Main/admin.cpp ./Admin/adminHelper.cpp -o admin

clean:
	sudo rm student hod instructor admin
