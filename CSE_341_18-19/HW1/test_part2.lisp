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

(setq globlist '()) ;Globlist: is the output list

(defun merge-list (firstlist secondlist) ;Main function only calls for helpers
	(helper-for-first firstlist)
	(helper-for-second secondlist)
)
(defun helper-for-first (firstlist)	
	(if (null firstlist)	; Recursion stopper
		(return-from helper-for-first 0)
	)
	(push (car firstlist) globlist)	
	(helper-for-first (cdr firstlist)) ; Expected recursion call
)
(defun helper-for-second (secondlist)
	(if (null secondlist); Recursion stopper
		(return-from helper-for-second 0)
	)
	(push (car secondlist) globlist)
	(helper-for-second (cdr secondlist)); Expected recursion call
)

;; MAIN FUNCTION
(defun main ()
  (with-open-file (stream #p"input_part2.csv")
    (loop :for line := (read-csv-line stream) :while line :collect
      (format t "~a~%"
      ;; CALL YOUR (MAIN) FUNCTION HERE
      	(setq globlist NIL)
		(merge-list (read-from-string (nth 0 line)) (read-from-string (nth 1 line)))
		(print (reverse globlist))
      )
    )
  )
)

;; CALL MAIN FUNCTION
(main)
;(merge-list '(1 2 3) '(a b c)) ; Example execution if needed 
;(setq globlist (reverse globlist)) ; This line is necessary since I pushed the elements reversely
;(print globlist) ; Optional print function to see the output list