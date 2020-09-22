(setq temp '()) ;Just a list used for some much things

(defun patch (token)	;Function that takes care of the words without parenthesis
	(if (not(equal token NIL))
		(progn
			(if (not(check_int token))
				(check_id token)
			)
		)
	)	
)
(defun check_int (token)	;Function that checks if the word is an integer
	(if (or(or(or(or(or(or(or(or(or(string= (car token) "0") (string= (car token) "1")) (string= (car token) "2"))(string= (car token) "3"))
(string= (car token) "4"))(string= (car token) "5"))(string= (car token) "6"))(string= (car token) "7"))(string= (car token) "8"))(string= (car token) "9"))
		(progn
			(format t "~C\"integer ~a\"" #\return (car token))
			(return-from check_int t)
		)
		(return-from check_int NIL)
	)
)
(defun check_id (token) ;Function that checks if the word is an identifier
	(print "identifier")
	(format t "~C\"identifier ~a\"" #\return token)

)
(defun check_and (token) ;Function that checks if the keyword is and
	(if (string= (car token) "a")
		(progn
			(setq token (cdr token))
			(if (string= (car token) "n")
				(progn
					(setq token (cdr token))
					(if (string= (car token) "d")
						(progn
							(print "keyword and")	
							(return-from check_and t)	
						)
						(return-from check_and NIL)	
					)
				)
			)
		)
	)
)
(defun check_or (token) ;Function that checks if the keyword is or
	(if (string= (car token) "o")
		(progn
			(setq token (cdr token))
			(if (string= (car token) "r")
				(progn
					(print "keyword or")
					(return-from check_or t)	
				)
				(return-from check_or NIL)
			)
		)
	)
)
(defun check_not (token) ;Function that checks if the keyword is not
	(if (string= (car token) "n")
		(progn
			(setq token (cdr token))
			(if (string= (car token) "o")
				(progn
					(setq token (cdr token))
					(if (string= (car token) "t")
						(progn
							(print "keyword not")	
							(return-from check_not t)
						)	
						(return-from check_not NIL)
					)
				)
			)
		)
	)
)
(defun check_equal (token);Function that checks if the keyword is equal
	(if (string= (car token) "e")
			(progn
				(setq token (cdr token))
				(if (string= (car token) "q")
					(progn
						(setq token (cdr token))
						(if (string= (car token) "u")
							(progn
								(setq token (cdr token))
								(if (string= (car token) "a")
									(progn
										(setq token (cdr token))
										(if (string= (car token) "l")
											(progn
												(print "keyword equal")
												(return-from check_equal t)													
											)
											(return-from check_equal NIL)	
										)
									)
								)
							)
						)
					)
				)
			)
	)	
)
(defun check_append (token) ;Function that checks if the keyword is append
	(if (string= (car token) "a")
			(progn
				(setq token (cdr token))
				(if (string= (car token) "p")
					(progn
						(setq token (cdr token))
						(if (string= (car token) "p")
							(progn
								(setq token (cdr token))
								(if (string= (car token) "e")
									(progn
										(setq token (cdr token))
										(if (string= (car token) "n")
											(progn
												(setq token (cdr token))
												(if (string= (car token) "d")
													(progn
														(print "keyword append")	
														(return-from check_append t)	
													)	
													(return-from check_append NIL)						
												)
											)
										)
									)
								)
							)
						)
					)
				)
			)

	)
)
(defun check_concat (token) ;Function that checks if the keyword is concat
	(if (string= (car token) "c")
			(progn
				(setq token (cdr token))
				(if (string= (car token) "o")
					(progn
						(setq token (cdr token))
						(if (string= (car token) "n")
							(progn
								(setq token (cdr token))
								(if (string= (car token) "c")
									(progn
										(setq token (cdr token))
										(if (string= (car token) "a")
											(progn
												(setq token (cdr token))
												(if (string= (car token) "t")
													(progn
														(print "keyword concat")	
														(return-from check_concat t)	
													)
													(return-from check_concat NIL)								
												)
											)
										)
									)
								)
							)
						)
					)
				)
			)
	)
)
(defun check_for (token) ;Function that checks if the keyword is for
	(if (string= (car token) "f")
		(progn
			(setq token (cdr token))
			(if (string= (car token) "o")
				(progn
					(setq token (cdr token))
					(if (string= (car token) "r")
						(progn
							(print "keyword for")	
							(return-from check_for t)	
						)
						(return-from check_for NIL)
					)
				)
			)
		)
	)	
)
(defun check_while (token) ;Function that checks if the keyword is while
		(if (string= (car token) "w")
			(progn
				(setq token (cdr token))
				(if (string= (car token) "h")
					(progn
						(setq token (cdr token))
						(if (string= (car token) "i")
							(progn
								(setq token (cdr token))
								(if (string= (car token) "l")
									(progn
										(setq token (cdr token))
										(if (string= (car token) "e")
											(progn
												(print "keyword while")
												(return-from check_while t)	
											)
											(return-from check_while NIL)	
										)
									)
								)
							)
						)
					)
				)
			)
	)	
)
(defun check_if (token) ;Function that checks if the keyword is if
	(if (string= (car token) "i")
		(progn
			(setq token (cdr token))
			(if (string= (car token) "f")
				(progn
					(print "keyword if")
					(return-from check_if t)	
				)
				(return-from check_if NIL)
			)
		)
	)
)
(defun check_exit (token) ;Function that checks if the keyword is exit
	(if (string= (car token) "e")
			(progn
				(setq token (cdr token))
				(if (string= (car token) "x")
					(progn
						(setq token (cdr token))
						(if (string= (car token) "i")
							(progn
								(setq token (cdr token))
								(if (string= (car token) "t")
									(progn
										(print "keyword exit")
										(return-from check_exit t)	
									)
									(return-from check_exit NIL)	
								)
							)
						)
					)
				)
			)
	)	
)
(defun check_set (token) ;Function that checks if the keyword is set
	(if (string= (car token) "s")
		(progn
			(setq token (cdr token))
			(if (string= (car token) "e")
				(progn
					(setq token (cdr token))
					(if (string= (car token) "t")
						(progn
							(print "keyword set")	
							(return-from check_set t)	
						)
						(return-from check_set NIL)
					)
				)
			)
		)
	)
)
(defun check_deffun (token);Function that checks if the keyword is deffun
	(if (string= (car token) "d")
			(progn
				(setq token (cdr token))
				(if (string= (car token) "e")
					(progn
						(setq token (cdr token))
						(if (string= (car token) "f")
							(progn
								(setq token (cdr token))
								(if (string= (car token) "f")
									(progn
										(setq token (cdr token))
										(if (string= (car token) "u")
											(progn
												(setq token (cdr token))
												(if (string= (car token) "n")
													(progn
														(print "keyword deffun")
														(return-from check_deffun t)	
													)
													(return-from check_deffun NIL)							
												)
											)
										)
									)
								)
							)
						)
					)
				)
			)
	)
)
(defun check_keyword (token) ;Function that checks if the word is a keyword
	(if(or(or(or(or(or(or(or(or(or(or(or (check_deffun token) (check_and token)) (check_or token)) (check_not token))
		(check_equal token)) (check_append token)) (check_concat token)) (check_for token))
		(check_while token)) (check_if token)) (check_exit token)) (check_set token))
		(return-from check_keyword t)
		(return-from check_keyword NIL)
	)	

)
(defun token_taken (token)	;Function that takes a token and names it
	(if (not (check_keyword token))
		(if (string= (car token) "+")
			(print "operator +")
			(progn
				(if (string= (car token) "-")
					(print "operator -")
					(progn
						(if (string= (car token) "/")
							(print "operator /")
							(progn
								(if (string= (car token) "*")
									(print "operator *")
									(progn
										(if (string= (car token) "**")
											(print "operator **")
											(progn 
												(if (not(check_int token))
													(check_id token)
												)												
											)
										)
									)
								)
							)
						)
					)
				)
			)
		)
	)
	
)

(defun word_taken (word) ;Function that takes a word and tokenizes it
	(setq word (reverse word))
	(setq backup word)
	(setq control 1)
	(loop
		(if (string= (car word) "(")
			(progn
				(print "operator (")
				(token_taken (cdr word))
				(setq control 0)
			)
			(progn
				(if (string= (car word) ")")
					(progn
						(print "operator )")
						(setq control 0)
					)
				)
			)
		)		
		(setq word (cdr word))
		(when (atom word) (return 0))
	)
	(if (= control 1)
		(patch backup)
	)
)

(defun analyze (line) ;The general analyzer that takes a code line
	(loop for i across line 
		do
		(if (and (string/= i " ") (string/= i #\Tab))
			(push i temp)
			(progn
				(word_taken temp)
				(setq temp '())
			)
		)
	)
)

(defun lexer (filename) ;Function that starts the whole procedure
	(let ((in (open filename :if-does-not-exist nil)))
	   (when in
	      (loop for line = (read-line in nil)
	      
	      while line do (analyze line))	      
	   )
	   	(close in)
	)	
)	

;(lexer "alp.txt") ;Example call with file name, the file should contain the program.
					 ;(Work for the samle input given in pdf)