;; Jason Brillante "Damdoshi"
;; Hanged Bunny Studio 2014-2019
;;
;; DABSIC Emacs mode
;; Thanks to tup-mode example: https://github.com/ejmr/tup-mode for colors
;; Thanks to the WPDL example mode for indentation
;;
;; TODO: Any indenting symbol inside inline commentaries is not ignored as it should.

(defconst dabsic-mode-version-number "1.0.0" "Dabsic mode version number.")
(defgroup dabsic nil "Major mode for editing Dabsic scripts"
  :group 'languages
  )
(defcustom dabsic-executable "/usr/local/bin/dabsic" "The Dabsic interpreter"
  :type 'string
  :group 'dabsic
  )
(defconst dabsic/keywords-regexp
  (regexp-opt
   (list "If" "Then" "EndIf" "ElseIf" "Else" "While" "EndWhile" "WEnd" "For" "To"
	 "Step" "EndFor" "Next" "Do" "AgainIf" "Repeat" "Until" "Select"
	 "Case" "EndSelect" "With" "EndWith" "Return" "Leave" "Break" "Brake"
	 "Continue" "Link" "Goto" "Wait" "Print" "PrintErr" "Exec"
	 "HaveValue" "NbrChildren" "NbrCase" "IsEmpty" "AddressOf" "Build" "Delete"
	 )
   'words)
  "Regular expression matching all Dabsic keywords."
  )
(defconst dabsic/directives-regexp
  "\\(?:^\\|\\s-\\)\\(@\\(insert\\|include\\|push\\)\\)"
  "Regular expression matching all Dabsic directives."
  )
(defconst dabsic/scopes-regexp
  "\\[\\(Function\\|Array\\|Sequence\\|CSV\\|Scope\\)"
  "Regular expression matching all Dabsic scopes explicit declaration."
  )
(defconst dabsic/nodes-regexp
  "\\(\\[\\|{\\)\\([a-zA-Z_]+[a-zA-Z0-9_]*\\)\\(const\\|eternal\\|solid\\)*"
  "Regular expression matching a Dabsic node opening."
  )
(defconst dabsic/node-specifiers-regexp
  "\\(const\\|eternal\\|solid\\)\\(\\!?\\)"
  "Regular expression matching a Dabsic node specifier opening."
  )
(defconst dabsic/fields-regexp
  "\\([a-zA-Z_]+[a-zA-Z0-9_]*\\).*="
  "Regular expression matching an Dabsic field assignation."
  )
(defconst dabsic/functions-regexp
  "\\([a-zA-Z_]+[a-zA-Z0-9_]*\\)("
  "Regular expression matching an Dabsic function declaration."
  )
(defconst dabsic/labels-regexp
  "\\([a-zA-Z_]+[a-zA-Z0-9_]*\\):"
  "Regular expression matching a Dabsic sequence label."
  )
(defconst dabsic/constants-regexp
  (regexp-opt
   (list "NULL"
	 "true"
	 "false")
   'words)
  "Regular expression matching all Dabsic constant values."
  )
(defconst dabsic/types-regexp
  (regexp-opt
   (list "integer"
	 "int"
	 "real"
	 "string")
   'words)
  "Regular expression matching all Dabsic types."
  )
(defconst dabsic/nodepth-regexp
  "^[ \t]*\\(\\[.*\\]\\|{.*}\\)"
  "Regular expression to not modify indentation depth."
  )
(defconst dabsic/indepth-regexp
  ".*\\(\\[\\|{\\|Then\\|While\\|For\\|Do\\|Repeat\\|Select\\|Case\\|With\\).*"
  "Regular expression to add a few indentation depth."
  )
(defconst dabsic/outdepth-regexp
  ".*\\(\\]\\|\\}\\|EndIf\\|EndWhile\\|WEnd\\|EndFor\\|Next\\|AgainIf\\|Until\\|EndSelect\\|EndWith\\)"
  "Regular expression to remove indentation depth."
  )
(defconst dabsic/outdepth-endline-regexp
  ".*\\(\\]\\|}\\|EndIf\\|EndWhile\\|WEnd\\|EndFor\\|Next\\|AgainIf\\|Until\\|EndSelect\\|EndWith\\)$"
  "Regular expression to remove a few indentation depth."
  )

;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defconst dabsic/font-lock-definitions
  (list
   (cons dabsic/directives-regexp font-lock-preprocessor-face)
   (cons dabsic/keywords-regexp font-lock-keyword-face)
   (cons dabsic/scopes-regexp '(1 font-lock-preprocessor-face))
   (cons dabsic/constants-regexp font-lock-constant-face)
   (cons dabsic/labels-regexp font-lock-constant-face)
   (cons dabsic/types-regexp font-lock-type-face)
   (cons dabsic/functions-regexp '(1 font-lock-function-name-face))
   (cons dabsic/nodes-regexp '(2 font-lock-type-face))
   (cons dabsic/node-specifiers-regexp '(1 font-lock-keyword-face))
   (cons dabsic/node-specifiers-regexp '(2 font-lock-comment-face))
   (cons dabsic/fields-regexp '(1 font-lock-variable-name-face))
   )
  "A map of regular expression to color characters"
  )

;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defconst dabsic-indent-width 2)
(defun dabsic-indent-line ()
  "Indent current line as Dabsic code."
  (interactive)
  (beginning-of-line)
  (if (bobp)
      (indent-line-to 0)   ; First line is always non-indented
    (let ((not-indented t) cur-indent)
      (if (looking-at dabsic/nodepth-regexp) ; If multiple openings
	  (progn
	    (setq cur-indent (current-indentation))
	    (setq not-indented nil))

	(if (looking-at dabsic/outdepth-endline-regexp) ; If the line we are looking at is the end of a block, then decrease the indentation
	    (progn
	      (save-excursion
		(forward-line -1)
		(setq cur-indent (- (current-indentation) dabsic-indent-width)))
	      (if (< cur-indent 0) ; We can't indent past the left margin
		  (setq cur-indent 0)))
	  (save-excursion
	    (while not-indented ; Iterate backwards until we find an indentation hint
	      (forward-line -1)
	      (if (looking-at dabsic/outdepth-regexp) ; This hint indicates that we need to indent at the level of the END_ token
		  (progn
		    (setq cur-indent (current-indentation))
		    (setq not-indented nil))
		(if (looking-at dabsic/indepth-regexp) ; This hint indicates that we need to indent an extra level
		    (progn
		      (setq cur-indent (+ (current-indentation) dabsic-indent-width)) ; Do the actual indenting
		      (setq not-indented nil))
		  (if (bobp)
		      (setq not-indented nil)))))))
	)
      (if cur-indent
	  (indent-line-to cur-indent)
	(indent-line-to 0))))) ; If we didn't see an indentation hint, then allow no indentation

(defvar dabsic-mode-syntax-table
  (let ((dabsic-mode-syntax-table (make-syntax-table)))
    ;; Allow _ to be a used inside variable name
    (modify-syntax-entry ?_ "w" dabsic-mode-syntax-table)
    ; Inline commentaries
    (modify-syntax-entry ?' "<" dabsic-mode-syntax-table)
    (modify-syntax-entry ?\n ">" dabsic-mode-syntax-table)
    ; Multi-line commentaries
    (modify-syntax-entry ?[ ". 1" dabsic-mode-syntax-table)
    (modify-syntax-entry ?* ". 23b" dabsic-mode-syntax-table)
    (modify-syntax-entry ?] "> 4" dabsic-mode-syntax-table)
    dabsic-mode-syntax-table)
    "Syntax table for dabsic-mode")

;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(local-set-key [tab] 'dabsic-indent-line)

(define-derived-mode dabsic-mode prog-mode "Dabsic"
  "Major mode for editing Dabsic scripts."

  (interactive)
  (set-syntax-table dabsic-mode-syntax-table)

  (set (make-local-variable 'font-lock-defaults) '(dabsic/font-lock-definitions nil t))
  (font-lock-mode 1)

  (set (make-local-variable 'indent-line-function) 'dabsic-indent-line)

  ;; Final newline is required
  (set (make-local-variable 'require-final-newline) t)
  ;; We use space
  (setq indent-tabs-mode nil)
  )

(progn
  (add-to-list 'auto-mode-alist '("\\.dab$" . dabsic-mode))
  )

(provide 'dabsic-mode)
