%-----ROOM FACTS----------

  room(z06).
  room(z11).

  rm_assign_capacity(z06, 10).
  rm_assign_capacity(z11, 10).

  rm_assign_handi(z06, yes).
  rm_assign_handi(z11, no).

  rm_assign_equipment(z06, projector).
  rm_assign_equipment(z11, smartboard).


%-------------------

%----- COURSE FACTS-------

  course(cse341).
  course(cse343).
  course(cse331).
  course(cse321).

  crs_assign_instructor(cse341, genc).
  crs_assign_instructor(cse343, turker).
  crs_assign_instructor(cse331, bayrakci).
  crs_assign_instructor(cse321, gozupek).

  crs_assign_capacity(cse341, 10).
  crs_assign_capacity(cse343, 6).
  crs_assign_capacity(cse331, 5).
  crs_assign_capacity(cse321, 10).

  crs_assign_room(cse341, z06).
  crs_assign_room(cse343, z11).
  crs_assign_room(cse331, z06).
  crs_assign_room(cse321, z11).


%-------------------

%---- INSTRUCTOR FACTS-------------------------
%
  instructor(genc).
  instructor(turker).
  instructor(bayrakci).
  instructor(gozupek).

  ins_assign_need(genc, projector).
  ins_assign_need(turker, smartboard).
  ins_assign_need(bayrakci, none).
  ins_assign_need(gozupek, smartboard).

  ins_assign_course(genc, cse341).
  ins_assign_course(turker, cse343).
  ins_assign_course(bayrakci, cse331).
  ins_assign_course(gozupek, cse321).

%------------------------------------------

%----- STUDENTS FACTS--------

  student(1).
  student(2).
  student(3).
  student(4).
  student(5).
  student(6).
  student(7).
  student(8).
  student(9).
  student(10).
  student(11).
  student(12).
  student(13).
  student(14).
  student(15).

  assign_course(1, cse341).
  assign_course(1, cse343).
  assign_course(1, cse331).
  assign_course(2, cse341).
  assign_course(2, cse343).
  assign_course(3, cse341).
  assign_course(3, cse331).
  assign_course(4, cse341).
  assign_course(5, cse343).
  assign_course(5, cse331).
  assign_course(6, cse341).
  assign_course(6, cse343).
  assign_course(6, cse331).
  assign_course(7, cse341).
  assign_course(7, cse343).
  assign_course(8, cse341).
  assign_course(8, cse331).
  assign_course(9, cse341).
  assign_course(10, cse341).
  assign_course(10, cse321).
  assign_course(11, cse341).
  assign_course(11, cse321).
  assign_course(12, cse343).
  assign_course(12, cse321).
  assign_course(13, cse343).
  assign_course(13, cse321).
  assign_course(14, cse343).
  assign_course(14, cse321).
  assign_course(15, cse343).
  assign_course(15, cse321).

  assign_hcap(1, no).
  assign_hcap(2, no).
  assign_hcap(3, no).
  assign_hcap(4, no).
  assign_hcap(5, no).
  assign_hcap(6, yes).
  assign_hcap(7, no).
  assign_hcap(8, yes).
  assign_hcap(9, no).
  assign_hcap(10, no).
  assign_hcap(11, no).
  assign_hcap(12, no).
  assign_hcap(13, no).
  assign_hcap(14, no).
  assign_hcap(15, yes).

%---------------------------
%-------- OCCUPANCY FACTS ---------

  occ_assign(8, z06, cse341).
  occ_assign(9, z06, cse341).
  occ_assign(10, z06, cse341).
  occ_assign(11, z06, cse341).
  occ_assign(12, z06, none).
  occ_assign(13, z06, cse331).
  occ_assign(14, z06, cse331).
  occ_assign(15, z06, cse331).
  occ_assign(16, z06, none).
  occ_assign(8, z06, cse343).
  occ_assign(9, z06, cse343).
  occ_assign(10, z11, cse343).
  occ_assign(11, z11, cse343).
  occ_assign(12, z11, none).
  occ_assign(13, z11, none).
  occ_assign(14, z11, cse321).
  occ_assign(15, z11, cse321).
  occ_assign(16, z11, cse321).
% ------------------------------------------------------------------------
% I changed the data a little bit in order to test my program. Z06
% doesn't support handicapped people. cse341 and cse343 conflictes two
% hours long at z06.
% ------------------------------------------------------------------------

  already_assigned(_student, _course) :- student(_student), course(_course), assign_course(_student, Course), (Course = _course).

  conflicts(_courseId1, _courseId2, _hourinfo, _classinfo) :- course(_courseId1), course(_courseId2), occ_assign(_hourinfo,_classinfo,_courseId1), occ_assign(_hourinfo,_classinfo, _courseId2), not(_courseId1 = _courseId2).

% conflicts:
%   course(): Checks if the variable is a course.
%   occ_assign(): Checks the occupancy table for _courseId1 and _courseId2.
%   not(): Makes sure that the program doesn't get confused when same
%   course was found.(Check out the documentation for
%   further information.)
%   -----------------------------------------------------------------------
%

  assign(RoomID, CourseID) :- room(RoomID), course(CourseID), rm_assign_capacity(RoomID, X),  crs_assign_capacity(CourseID, Y), X >= Y, crs_assign_room(CourseID, Z), Z = RoomID, rm_assign_equipment(RoomID, EQ), crs_assign_instructor(CourseID, INS), ins_assign_need(INS, NEED), NEED = EQ.

% Assign:
%   room(): Checks if the variable is a room.
%   course(): Checks if the variable is a course.
%   rm_assign_capacity(): Takes the chosen room's capacity.
%   crs_assign_capacity(): Takes the chosen course's capacity.
%   X >= Y: Compares those capacities.
%   crs_assign_room(): Takes the course's room.
%   Z = RoomID: Checks if the given RoomId is equal to the course's id.
%   room_assign_equipment(): Takes the room's equipment.
%   course_assign_instructor(): Takes the course's instructor.
%   ins_assign_need(): Takes the instructor's need.
%   NEED = EQ: Checks if the needs are equal.(Check out the documentation for
%   further information.)
%   -----------------------------------------------------------------------

  enroll(StudentID, CourseID):- ((assign_hcap(StudentID, HC), HC = 'yes') , crs_assign_room(CourseID, RM), rm_assign_handi(RM, HANDI), HANDI = 'yes') ; (assign_hcap(StudentID, HL), HL = 'no', course(CourseID), student(StudentID)),( not(already_assigned(StudentID, CourseID)) -> assert(assign_course(StudentID,CourseID))).

% enroll:
%   assign_hcap(): Takes the student's handicap state.
%   HC = 'yes': Checks if there is a handicap.
%   crs_assign_room(): Takes the course's room.
%   rm_assign_handi(): Takes the room's handicap state.
%   HANDI = 'yes': Checks if the room has the handicap quality.
%   assign_hcap(): Takes the student's handicap state.
%   HC = 'no': Checks if there is no handicap.
%   already_assigned(): Checks if the student is already enrolled to the
%   course.
%   assert(assign_course()): Enrolls the student to the course.(Check out the documentation for
%   further information.)
%-----------------------------------------------------------------------
