install: copy student instructor hod admin
	cp student /usr/bin
	echo "completed installing"

installLocal: student instructor hod admin
	echo "completed installing"
	
createGroups:
	pw groupadd --force students
	pw groupadd Faculty
	pw groupadd studentsexecute 
	pw groupadd facultyexecute
	pw groupadd hods

	
copy: 
	sudo mkdir -p /usr/share/osApp
	sudo cp -r Admin /usr/share/osApp
	sudo cp -r Daemon /usr/share/osApp
	sudo cp -r Database /usr/share/osApp
	sudo cp -r Hod /usr/share/osApp
	sudo cp -r Instructor /usr/share/osApp
	sudo cp -r Main /usr/share/osApp
	sudo cp Makefile /usr/share/osApp
	sudo cp -r Student /usr/share/osApp
	sudo cp -r UI /usr/share/osApp
	cd /usr/share/osApp

student: ./UI/content.cpp ./UI/editor.cpp ./Main/student.cpp ./Student/student.cpp ./Instructor/instructor_marks_list.cpp

	g++48 ./UI/content.cpp ./UI/editor.cpp ./Main/student.cpp ./Student/student.cpp ./Instructor/instructor_marks_list.cpp -o student -std=c++0x
	setfacl -m u::--- student
	setfacl -m g::--x student
	setfacl -m g:students:--x student
	setfacl -m o::--- student
	sudo chown root:studentsexecute student
	sudo chmod g+s student

instructor: ./UI/content.cpp ./UI/editor.cpp ./Main/instructor.cpp ./Student/student.cpp ./Instructor/instructor_marks_list.cpp
	g++48 ./UI/content.cpp ./UI/editor.cpp ./Main/instructor.cpp ./Student/student.cpp ./Instructor/instructor_marks_list.cpp -o instructor -std=c++11
	setfacl -m u::--- instructor
	setfacl -m g::--x instructor
	setfacl -m g:Faculty:--x instructor
	setfacl -m o::--- instructor
	sudo chown root:facultyexecute instructor
	sudo chmod g+s instructor

hod: ./UI/content.cpp ./UI/editor.cpp ./Main/hod.cpp ./Hod/hod.cpp ./Instructor/instructor_marks_list.cpp
	g++48 ./UI/content.cpp ./UI/editor.cpp ./Main/hod.cpp ./Hod/hod.cpp ./Instructor/instructor_marks_list.cpp -o hod -std=c++11
	setfacl -m u::--- hod
	setfacl -m g::--x hod
	setfacl -m g:hods:--x hod
	setfacl -m o::--- hod
	sudo chown root:studentsexecute hod
	sudo chmod g+s hod

admin: ./UI/content.cpp ./UI/editor.cpp ./Main/admin.cpp ./Admin/adminHelper.cpp
	g++48 ./UI/content.cpp ./UI/editor.cpp ./Main/admin.cpp ./Admin/adminHelper.cpp -o admin -std=c++11
	setfacl -m u::--x admin
	setfacl -m g::--- admin
	setfacl -m o::--- admin
	sudo chown root admin


clean:
	sudo rm student hod instructor admin
