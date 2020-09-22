(load "csv-parser.lisp")
(in-package :csv-parser)

;; (read-from-string STRING)
;; This function converts the input STRING to a lisp object.
;; In this code, I use this function to convert lists (in string format) from csv file to real lists.

;; (nth INDEX LIST)
;; This function allows us to access value at INDEX of LIST.
;; Example: (nth 0 '(a b c)) => a

;; !!! VERY VERY VERY IMPORTANT NOTE !!!
;; FOR EACH ARGUMENT IN CSV FILE
;; USE THE CODE (read-from-string (nth ARGUMENT-INDEX line))
;; Example: (mypart1-funct (read-from-string (nth 0 line)) (read-from-string (nth 1 line)))

;; DEFINE YOUR FUNCTION(S) HERE
(setq globlist '())
(defun list-leveller (thelist)
	(if (listp (car thelist))
		(list-leveller (car thelist)) ;Expected recursive call if a list
		(push (car thelist) globlist) ; Push function if not a list
	)	
	(setq thelist (cdr thelist)) ; Shrinks the list
	(if (null thelist)
		(return-from list-leveller 0) ;Stops the recursion if list is empty
		(list-leveller thelist) ;Expected recursive call if list is not empty
	)
)

;; MAIN FUNCTION
(defun main ()
  (with-open-file (stream #p"input_part1.csv")
    (loop :for line := (read-csv-line stream) :while line :collect
      (format t "~a~%"
      ;; CALL YOUR (MAIN) FUNCTION HERE
      (setq globlist NIL)  ;Globlist: is the output list
      (list-leveller (read-from-string (nth 0 line)))
      (print (reverse globlist)) ; This line is necessary since I pushed the elements reversely

      )
    )
  )
)

;; CALL MAIN FUNCTION
(main)