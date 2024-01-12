a.out : *.cpp
	g++ *.cpp

move_easy:
	mv *.cpp ./Easy/
	make clean

move_med : 
	mv *.cpp ./Medium/
	make clean

move_hard :
	mv *.cpp ./Hard
	make clean

clean : 
	rm *.out
	clear

format :
	sed -i 's/Input:/Input-/g' *.cpp
	sed -i 's/Output:/Output-/g' *.cpp
	sed -i 's/Constraints:/Constraints-/g' *.cpp
