;; Jason Brillante "Damdoshi"
;; Hanged Bunny Studio 2014-2026
;;
;; DABSIC Emacs mode
;;
;; This version keeps the mode intentionally lightweight, but makes indentation
;; aware of the embedded formats accepted by Bunny Configuration / Dabsic:
;; scopes, arrays, functions, sequences, CSV blocks, XML-like markup and
;; disabled blocks introduced with [!, {! or <!.

(defconst dabsic-mode-version-number "1.1.0" "Dabsic mode version number.")

(defgroup dabsic nil "Major mode for editing Dabsic scripts"
  :group 'languages)

(defcustom dabsic-executable "/usr/local/bin/dabsic" "The Dabsic interpreter"
  :type 'string
  :group 'dabsic)

(defconst dabsic/keywords-regexp
  (regexp-opt
   (list "If" "Then" "EndIf" "ElseIf" "Else" "While" "EndWhile" "WEnd" "For" "To"
         "Step" "EndFor" "Next" "Do" "AgainIf" "Repeat" "Until" "Select"
         "Case" "EndSelect" "With" "EndWith" "Return" "Leave" "Break" "Brake"
         "Continue" "Link" "Goto" "Wait" "Print" "PrintErr" "Exec"
         "HaveValue" "NbrChildren" "NbrCase" "IsEmpty" "AddressOf" "Build" "Delete")
   'words)
  "Regular expression matching all Dabsic keywords.")

(defconst dabsic/directives-regexp
  "\\(?:^\\|\\s-\\)\\(@\\(insert\\|include\\|push\\)\\)"
  "Regular expression matching all Dabsic directives.")

(defconst dabsic/scopes-regexp
  "\\[\\(Function\\|Array\\|Data\\|Sequence\\|CSV\\|Scope\\|Node\\|Text\\)"
  "Regular expression matching all Dabsic explicit scope declarations.")

(defconst dabsic/nodes-regexp
  "\\(\\[\\|{\\)\\([a-zA-Z_]+[a-zA-Z0-9_]*\\)\\(const\\|eternal\\|solid\\)*"
  "Regular expression matching a Dabsic node opening.")

(defconst dabsic/node-specifiers-regexp
  "\\(const\\|eternal\\|solid\\)\\(\\!?\\)"
  "Regular expression matching a Dabsic node specifier opening.")

(defconst dabsic/fields-regexp
  "\\([a-zA-Z_]+[a-zA-Z0-9_]*\\).*="
  "Regular expression matching a Dabsic field assignation.")

(defconst dabsic/functions-regexp
  "\\([a-zA-Z_]+[a-zA-Z0-9_]*\\)("
  "Regular expression matching a Dabsic function declaration or call.")

(defconst dabsic/labels-regexp
  "^[ \t]*\\([a-zA-Z_]+[a-zA-Z0-9_]*\\):"
  "Regular expression matching a Dabsic sequence label.")

(defconst dabsic/constants-regexp
  (regexp-opt (list "NULL" "true" "false") 'words)
  "Regular expression matching all Dabsic constant values.")

(defconst dabsic/types-regexp
  (regexp-opt (list "integer" "int" "real" "string") 'words)
  "Regular expression matching all Dabsic types.")

(defconst dabsic/commented-block-regexp
  "^[ \t]*\\(?:\\[!\\|{!\\|<!\\)"
  "Regular expression matching Dabsic disabled block openings.")

(defconst dabsic/xml-markup-regexp
  "^[ \t]*</?[@a-zA-Z_][a-zA-Z0-9_:-]*\\(?:[ \t\n][^>]*\\)?>"
  "Regular expression matching an XML-ish markup line.")

(defconst dabsic/font-lock-definitions
  (list
   (cons dabsic/directives-regexp font-lock-preprocessor-face)
   (cons dabsic/commented-block-regexp font-lock-comment-face)
   (cons dabsic/keywords-regexp font-lock-keyword-face)
   (cons dabsic/scopes-regexp '(1 font-lock-preprocessor-face))
   (cons dabsic/constants-regexp font-lock-constant-face)
   (cons dabsic/labels-regexp '(1 font-lock-constant-face))
   (cons dabsic/types-regexp font-lock-type-face)
   (cons dabsic/functions-regexp '(1 font-lock-function-name-face))
   (cons dabsic/xml-markup-regexp font-lock-preprocessor-face)
   (cons dabsic/nodes-regexp '(2 font-lock-type-face))
   (cons dabsic/node-specifiers-regexp '(1 font-lock-keyword-face))
   (cons dabsic/node-specifiers-regexp '(2 font-lock-comment-face))
   (cons dabsic/fields-regexp '(1 font-lock-variable-name-face)))
  "A map of regular expression to font-lock faces.")

(defconst dabsic-indent-width 2)

(defun dabsic--trim (s)
  "Return S without leading or trailing whitespace."
  (replace-regexp-in-string "\\`[ \t\n\r]+\\|[ \t\n\r]+\\'" "" s))

(defun dabsic--line-string ()
  "Return the current line as a string."
  (buffer-substring-no-properties (line-beginning-position) (line-end-position)))

(defun dabsic--strip-inline-comment (s)
  "Remove a Dabsic inline comment from S, preserving apostrophes in strings."
  (let ((i 0)
        (len (length s))
        (in-string nil)
        (escaped nil)
        (cut nil))
    (while (and (< i len) (not cut))
      (let ((ch (aref s i)))
        (cond
         (escaped
          (setq escaped nil))
         ((and in-string (= ch ?\\))
          (setq escaped t))
         ((= ch ?\")
          (setq in-string (not in-string)))
         ((and (not in-string) (= ch ?'))
          (setq cut i))))
      (setq i (1+ i)))
    (if cut (substring s 0 cut) s)))

(defun dabsic--code-line ()
  "Return current line stripped from inline comments and surrounding spaces."
  (dabsic--trim (dabsic--strip-inline-comment (dabsic--line-string))))

(defun dabsic--blank-or-comment-p (s)
  "Return non-nil when S is blank or an inline Dabsic comment."
  (or (string= s "")
      (string-prefix-p "'" s)))

(defun dabsic--stack-top (stack)
  "Return top element of STACK."
  (car stack))

(defun dabsic--stack-entry-kind (entry)
  "Return the symbolic kind of an indentation stack ENTRY."
  (if (consp entry) (car entry) entry))

(defun dabsic--stack-top-kind (stack)
  "Return the symbolic kind of the top element of STACK."
  (dabsic--stack-entry-kind (car stack)))

(defun dabsic--push (kind stack)
  "Push KIND on STACK."
  (cons kind stack))

(defun dabsic--pop (stack)
  "Pop STACK without failing on an empty stack."
  (if stack (cdr stack) nil))

(defun dabsic--pop-function-block (stack)
  "Pop one function-local indentation block from STACK."
  (cond
   ((memq (dabsic--stack-top-kind stack) '(func-block func-single))
    (cdr stack))
   (t stack)))

(defun dabsic--context-kind (stack)
  "Return the nearest real format context from STACK."
  (let ((s stack)
        found)
    (while (and s (not found))
      (if (memq (dabsic--stack-entry-kind (car s))
                '(function sequence csv text xml scope array disabled-square disabled-curly disabled-angle))
          (setq found (dabsic--stack-entry-kind (car s)))
        (setq s (cdr s))))
    found))

(defun dabsic--inside-function-p (stack)
  "Return non-nil if STACK is currently inside a Dabsic function."
  (memq 'function stack))

(defun dabsic--inside-sequence-p (stack)
  "Return non-nil if STACK is currently inside a Dabsic sequence."
  (eq (dabsic--context-kind stack) 'sequence))

(defun dabsic--inside-csv-p (stack)
  "Return non-nil if STACK is currently inside a CSV block."
  (eq (dabsic--context-kind stack) 'csv))

(defun dabsic--inside-text-p (stack)
  "Return non-nil if STACK is currently inside a Text block."
  (eq (dabsic--context-kind stack) 'text))

(defun dabsic--disabled-close-regexp (kind)
  "Return the closing regexp for disabled block KIND."
  (cond
   ((eq kind 'disabled-square) "^") ; placeholder, not used directly
   ((eq kind 'disabled-curly) "^")
   ((eq kind 'disabled-angle) "^")
   (t "^$")))

(defun dabsic--line-opens-disabled (s)
  "Return disabled block kind opened by S, or nil."
  (cond
   ((string-match-p "^\\[!" s) 'disabled-square)
   ((string-match-p "^{!" s) 'disabled-curly)
   ((string-match-p "^<!" s) 'disabled-angle)
   (t nil)))

(defun dabsic--unquote-token (s)
  "Return S without surrounding single or double quotes when present."
  (let ((len (length s)))
    (if (and (>= len 2)
             (or (and (= (aref s 0) ?\") (= (aref s (1- len)) ?\"))
                 (and (= (aref s 0) ?') (= (aref s (1- len)) ?'))))
        (substring s 1 (1- len))
      s)))

(defun dabsic--split-text-arguments (s)
  "Split a Text argument list S on top-level commas."
  (let ((i 0)
        (len (length s))
        (start 0)
        (paren-depth 0)
        (bracket-depth 0)
        (brace-depth 0)
        (in-string nil)
        (escaped nil)
        (parts nil))
    (while (< i len)
      (let ((ch (aref s i)))
        (cond
         (escaped
          (setq escaped nil))
         ((and in-string (= ch ?\\))
          (setq escaped t))
         ((= ch ?\")
          (setq in-string (not in-string)))
         ((not in-string)
          (cond
           ((= ch ?\() (setq paren-depth (1+ paren-depth)))
           ((= ch ?\)) (setq paren-depth (max 0 (1- paren-depth))))
           ((= ch ?[) (setq bracket-depth (1+ bracket-depth)))
           ((= ch ?]) (setq bracket-depth (max 0 (1- bracket-depth))))
           ((= ch ?{) (setq brace-depth (1+ brace-depth)))
           ((= ch ?}) (setq brace-depth (max 0 (1- brace-depth))))
           ((and (= ch ?,)
                 (= paren-depth 0)
                 (= bracket-depth 0)
                 (= brace-depth 0))
            (setq parts (cons (substring s start i) parts))
            (setq start (1+ i)))))))
      (setq i (1+ i)))
    (nreverse (cons (substring s start) parts))))

(defun dabsic--line-opens-text (s)
  "Return a Text stack entry opened by S, or nil.

Text blocks are closed by the marker passed as the last Text argument,
followed by a closing bracket. For example [Text($,Footer) closes on Footer]."
  (when (string-match "\\[Text[ \t]*(\\(.*\\))[ \t]*$" s)
    (let* ((args (dabsic--split-text-arguments (match-string 1 s)))
           (last-arg (and args (car (last args))))
           (marker (and last-arg
                        (dabsic--unquote-token (dabsic--trim last-arg)))))
      (when (and marker (not (string= marker "")))
        (cons 'text marker)))))

(defun dabsic--line-closes-text-p (s entry)
  "Return non-nil when S closes the Text block represented by ENTRY."
  (and (consp entry)
       (eq (car entry) 'text)
       (string-match-p (concat "^" (regexp-quote (cdr entry)) "\\][ \t]*$") s)))

(defun dabsic--line-closes-disabled-p (s kind)
  "Return non-nil when S closes disabled block KIND."
  (cond
   ((eq kind 'disabled-square) (string-match-p "\\]" s))
   ((eq kind 'disabled-curly) (string-match-p "}" s))
   ((eq kind 'disabled-angle) (string-match-p ">" s))
   (t nil)))

(defun dabsic--function-closing-line-p (s)
  "Return non-nil if S closes a function control block."
  (string-match-p
   "^\\(EndIf\\|ElseIf\\|Else\\|EndWhile\\|WEnd\\|EndFor\\|Next\\|AgainIf\\|Until\\|EndSelect\\|Case\\|EndWith\\)\\_>" s))

(defun dabsic--function-reopens-after-close-p (s)
  "Return non-nil if S closes a block and immediately opens a sibling block."
  (string-match-p "^\\(ElseIf\\|Else\\|Case\\)\\_>" s))

(defun dabsic--function-block-opener-p (s)
  "Return non-nil if S opens a multi-line function control block."
  (cond
   ;; In Dabsic, Then introduces one statement. It must not behave like EndIf-less block indentation forever.
   ((string-match-p "^If\\_>" s)
    (not (string-match-p "\\_<Then\\_>" s)))
   ((string-match-p "^\\(While\\|For\\|Do\\|Repeat\\|Select\\|With\\)\\_>" s) t)
   (t nil)))

(defun dabsic--function-single-opener-p (s)
  "Return non-nil if S opens a one-statement function indentation level."
  (and (string-match-p "^If\\_>" s)
       (string-match-p "\\_<Then[ \t]*$" s)))

(defun dabsic--xml-opening-line-p (s)
  "Return non-nil if S opens an XML-like element."
  (and (string-match-p "^<[@a-zA-Z_][a-zA-Z0-9_:-]*\\(?:[ \t][^>]*\\)?>" s)
       (not (string-match-p "^</" s))
       (not (string-match-p "/>[ \t]*$" s))))

(defun dabsic--xml-closing-line-p (s)
  "Return non-nil if S begins with an XML-like closing element."
  (string-match-p "^</" s))

(defun dabsic--opens-container-kind (s)
  "Return the Dabsic container kind opened by S, or nil."
  (let ((start (or (and (string-match "=\\s-*\\(\\[\\|{\\)" s)
                        (match-beginning 1))
                   (and (string-match "^\\(\\[\\|{\\)" s)
                        (match-beginning 1)))))
    (when start
      (let ((tail (substring s start)))
        (cond
         ;; Do not mistake [] path/root expressions for real containers.
         ((string-match-p "^\\[\\]" tail) nil)
         ((string-match-p "^\\[\\." tail) nil)
         ((string-match-p "^\\[!" tail) 'disabled-square)
         ((string-match-p "^{!" tail) 'disabled-curly)
         ((and (string-match-p "^\\[CSV\\_>" tail)
               (not (string-match-p "\\][ \t]*$" tail)))
          'csv)
         ((and (string-match-p "^\\[Sequence\\_>" tail)
               (not (string-match-p "\\][ \t]*$" tail)))
          'sequence)
         ((and (string-match-p "^\\[Function\\_>" tail)
               (not (string-match-p "\\][ \t]*$" tail)))
          'function)
         ((and (string-match-p "^\\[\\(Array\\|Data\\)\\_>" tail)
               (not (string-match-p "\\][ \t]*$" tail)))
          'array)
         ((and (string-match-p "^\\[\\(Scope\\|Node\\)\\_>" tail)
               (not (string-match-p "\\][ \t]*$" tail)))
          'scope)
         ((string-match-p "^\\[Text[ \t]*(" tail)
          nil)
         ((and (string-match-p "^\\[[a-zA-Z_]" tail)
               (not (string-match-p "\\][ \t]*$" tail)))
          'scope)
         ((and (string-match-p "^{[a-zA-Z_]" tail)
               (not (string-match-p "}[ \t]*$" tail)))
          'array)
         (t nil))))))

(defun dabsic--update-stack-with-line (stack s)
  "Return STACK updated after reading already-indented code line S."
  (let ((active-single (eq (dabsic--stack-top-kind stack) 'func-single)))
    (cond
     ((dabsic--blank-or-comment-p s)
      stack)
     ((memq (dabsic--stack-top-kind stack) '(disabled-square disabled-curly disabled-angle))
      (if (dabsic--line-closes-disabled-p s (dabsic--stack-top-kind stack))
          (cdr stack)
        stack))
     ((eq (dabsic--stack-top-kind stack) 'text)
      (if (dabsic--line-closes-text-p s (dabsic--stack-top stack))
          (cdr stack)
        stack))
     ((dabsic--inside-csv-p stack)
      (if (string-match-p "^\\]" s)
          (dabsic--pop stack)
        stack))
     ((dabsic--inside-sequence-p stack)
      (if (string-match-p "^\\]" s)
          (dabsic--pop stack)
        stack))
     ((eq (dabsic--context-kind stack) 'xml)
      (cond
       ((dabsic--xml-closing-line-p s)
        (dabsic--pop stack))
       ((dabsic--xml-opening-line-p s)
        (dabsic--push 'xml stack))
       (t stack)))
     (t
      (let ((new-stack stack)
            kind)
        ;; Apply leading closers first: the current line is at the parent level.
        (cond
         ((string-match-p "^\\]" s)
          (setq new-stack (dabsic--pop new-stack)))
         ((string-match-p "^}" s)
          (setq new-stack (dabsic--pop new-stack)))
         ((and (dabsic--inside-function-p new-stack)
               (dabsic--function-closing-line-p s))
          (setq new-stack (dabsic--pop-function-block new-stack))))

        ;; Some function closers are also sibling openers.
        (when (and (dabsic--inside-function-p new-stack)
                   (dabsic--function-reopens-after-close-p s))
          (setq new-stack (dabsic--push 'func-block new-stack)))

        ;; Generic format/container openings.
        (setq kind (or (dabsic--line-opens-disabled s)
                       (dabsic--line-opens-text s)
                       (dabsic--opens-container-kind s)
                       (and (dabsic--xml-opening-line-p s) 'xml)))
        (when kind
          (setq new-stack (dabsic--push kind new-stack)))

        ;; Function control openings, but only when the current context really is a function.
        (when (dabsic--inside-function-p new-stack)
          (cond
           ((dabsic--function-single-opener-p s)
            (setq new-stack (dabsic--push 'func-single new-stack)))
           ((dabsic--function-block-opener-p s)
            (setq new-stack (dabsic--push 'func-block new-stack)))))

        ;; A func-single that existed before reading this line expires after this line.
        (when active-single
          ;; Remove the first func-single still present in the stack. Usually it is at the top,
          ;; unless the single statement opened an inner block of its own.
          (let ((head nil)
                (tail new-stack)
                done)
            (while (and tail (not done))
              (if (eq (car tail) 'func-single)
                  (progn
                    (setq new-stack (append (nreverse head) (cdr tail)))
                    (setq done t))
                (setq head (cons (car tail) head))
                (setq tail (cdr tail))))))
        new-stack)))))

(defun dabsic--stack-before-current-line ()
  "Return indentation stack before the current line."
  (let ((target (line-beginning-position))
        (stack nil))
    (save-excursion
      (goto-char (point-min))
      (while (< (point) target)
        (let ((s (dabsic--code-line)))
          (setq stack (dabsic--update-stack-with-line stack s)))
        (forward-line 1)))
    stack))

(defun dabsic--indent-for-line (stack s)
  "Return indentation for current line S given previous indentation STACK."
  (let ((depth (length stack)))
    (cond
     ((dabsic--blank-or-comment-p s)
      nil)
     ((and (memq (dabsic--stack-top-kind stack) '(disabled-square disabled-curly disabled-angle))
           (dabsic--line-closes-disabled-p s (dabsic--stack-top-kind stack)))
      (* (max 0 (1- depth)) dabsic-indent-width))
     ((and (eq (dabsic--stack-top-kind stack) 'text)
           (dabsic--line-closes-text-p s (dabsic--stack-top stack)))
      (* (max 0 (1- depth)) dabsic-indent-width))
     ((eq (dabsic--stack-top-kind stack) 'text)
      (* depth dabsic-indent-width))
     ((and (dabsic--inside-csv-p stack)
           (string-match-p "^\\]" s))
      (* (max 0 (1- depth)) dabsic-indent-width))
     ((and (dabsic--inside-sequence-p stack)
           (string-match-p "^\\]" s))
      (* (max 0 (1- depth)) dabsic-indent-width))
     ((and (dabsic--inside-sequence-p stack)
           (string-match-p dabsic/labels-regexp s))
      (max 0 (- (* depth dabsic-indent-width) (/ dabsic-indent-width 2))))
     ((and (eq (dabsic--context-kind stack) 'xml)
           (dabsic--xml-closing-line-p s))
      (* (max 0 (1- depth)) dabsic-indent-width))
     ((or (string-match-p "^\\]" s)
          (string-match-p "^}" s))
      (* (max 0 (1- depth)) dabsic-indent-width))
     ((and (dabsic--inside-function-p stack)
           (dabsic--function-closing-line-p s))
      (* (max 0 (1- depth)) dabsic-indent-width))
     (t
      (* depth dabsic-indent-width)))))

(defun dabsic-indent-line ()
  "Indent current line as Dabsic code, with embedded-format awareness."
  (interactive)
  (let* ((offset (- (point-max) (point)))
         (s (dabsic--code-line))
         (stack (dabsic--stack-before-current-line))
         (indent (dabsic--indent-for-line stack s)))
    (when indent
      (indent-line-to indent))
    (when (> (- (point-max) offset) (point))
      (goto-char (- (point-max) offset)))))

(defvar dabsic-mode-syntax-table
  (let ((dabsic-mode-syntax-table (make-syntax-table)))
    ;; Allow _ to be used inside variable names.
    (modify-syntax-entry ?_ "w" dabsic-mode-syntax-table)
    ;; Inline comments.
    (modify-syntax-entry ?' "<" dabsic-mode-syntax-table)
    (modify-syntax-entry ?\n ">" dabsic-mode-syntax-table)
    ;; Multi-line comments: [* ... *]
    (modify-syntax-entry ?\[ ". 1" dabsic-mode-syntax-table)
    (modify-syntax-entry ?\* ". 23b" dabsic-mode-syntax-table)
    (modify-syntax-entry ?\] "> 4" dabsic-mode-syntax-table)
    dabsic-mode-syntax-table)
  "Syntax table for dabsic-mode.")

(defvar dabsic-mode-map
  (let ((map (make-sparse-keymap)))
    (define-key map (kbd "TAB") 'dabsic-indent-line)
    map)
  "Keymap for dabsic-mode.")

(define-derived-mode dabsic-mode prog-mode "Dabsic"
  "Major mode for editing Dabsic scripts."
  (set-syntax-table dabsic-mode-syntax-table)
  (set (make-local-variable 'font-lock-defaults) '(dabsic/font-lock-definitions nil t))
  (font-lock-mode 1)
  (set (make-local-variable 'indent-line-function) 'dabsic-indent-line)
  ;; Final newline is required.
  (set (make-local-variable 'require-final-newline) t)
  ;; We use spaces.
  (setq indent-tabs-mode nil))

(add-to-list 'auto-mode-alist '("\\.dab$" . dabsic-mode))

(provide 'dabsic-mode)
