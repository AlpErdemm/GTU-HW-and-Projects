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
 
(defun tracer (thelist theindex)	;Creates the first part of the list (before thenumber)
	(if (= theindex 0)
		(return-from tracer 0)
	)
	(push (car thelist) globlist)
	(tracer (cdr thelist) (- theindex 1)) ;Expected recursion call
)
(defun cleaner (thelist theindex thelength) ;Creates the last part of the list (after thenumber)
	(if (not (= theindex thelength))
		(progn
			(push (nth theindex thelist) globlist)
			(cleaner thelist (+ theindex 1) thelength) ;Expected recursion call
		)
	)
)
(defun insert-n (thelist thenumber theindex) ;Main function only calls for helpers
	(if (= theindex 0)
		(progn
			(push thenumber thelist)
			(setq globlist (reverse thelist))
			(return-from insert-n 0)
		)
	)
	(tracer thelist theindex)	; Essential function calls
	(push thenumber globlist)
	(cleaner thelist theindex (list-length thelist))
)

;; MAIN FUNCTION
(defun main ()
  (with-open-file (stream #p"input_part3.csv")
    (loop :for line := (read-csv-line stream) :while line :collect
      (format t "~a~%"
      ;; CALL YOUR (MAIN) FUNCTION HERE

      	(setq globlist NIL)
		(insert-n (read-from-string (nth 0 line)) (read-from-string (nth 1 line)) (read-from-string (nth 2 line)))
		(print (reverse globlist))

      )
    )
  )
)

;; CALL MAIN FUNCTION
(main)
