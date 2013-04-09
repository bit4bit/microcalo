;; Esto es basado en la documentacion de
;; derived-mode-ex.el
;; 27 actubre 2012

(require 'cc-mode)

(eval-when-compile
  (require 'cc-langs)
  (require 'cc-fonts))
(eval-and-compile
  (c-add-language 'cspa-mode 'c-mode))


;;Agregamos premitivas en espanol
(c-lang-defconst c-primitive-type-kwds
		 cspa (append '("entero" "real" "caracter" "punteroA" "estructura" "cadena" "binario") (c-lang-const c-primitive-type-kwds)
			      ))

;;Palabras claves
(c-lang-defconst c-modifier-kwds
		 cspa (append '("punteroA" "estructura" "mientras" "si" "aunque" "para" "cada" "siguiente" "hacer" "almenos" "pero" "cualquier" "cuando" "es" "retorna" "ciclo"))
		 )

(defvar cspa-mode-syntax-table nil
  "Tabla de sintaxs usada en CSPA mode")
(or cspa-mode-syntax-table
    (setq cspa-mode-syntax-table
	  (funcall (c-lang-const c-make-mode-syntax-table cspa))))

(defvar cspa-mode-abbrev-table nil
  "Tabla de abreviaciones usada por CSPA")
(c-define-abbrev-table 'cspa-mode-abbrev-table
		       '(("almenos" "almenos" c-electric-continued-statement 0)
			 ("mientras" "mientras" c-electric-continued-statement 0)
			 ("cada" "cada" c-electric-continued-statement 0)
			 ("hacer" "hacer" c-electric-continued-statement 0)
			 ("si" "si" c-electric-continued-statement 0)
			 ("ciclo" "ciclo" c-electric-continued-statement 0))
		       )

;;(easy-menu-define cspa-menu cspa-mode-map "CSPA Mode commands"
;;  (cons "CSPA" (c-lang-const c-mode-menu cspa)))
(defvar cspa-font-lock-keywords-3 (c-lang-const c-matchers-3 cspa)
  "Color CSPA mode")

(defvar cspa-font-lock-keywords cspa-font-lock-keywords-3
  "Por defecto color CSPA mode.")


(defun cspa-mode()
  "Major mode for editing CSPA code. Este es un modo mayor
para la edicion de codig CSPA C en espanol"
  (interactive)
  (kill-all-local-variables)
  (c-initialize-cc-mode t)
  (set-syntax-table cspa-mode-syntax-table)
  (setq major-mode 'cspa-mode
	mode-name "CSPA"
	local-abbrev-table cspa-mode-abbrev-table
	abbrev-mode t)
  (use-local-map c-mode-map)
  (c-init-language-vars cspa-mode)
  (c-common-init 'cspa-mode)
  ;;(easy-menu-add cspa-menu)
  (run-hooks 'c-mode-common-hook)
  (run-hooks 'c-mode-hook)
  (c-update-modeline))

(add-to-list 'auto-mode-alist '("\\.cspa\\'" . cspa-mode))


(provide 'cspa-mode)
