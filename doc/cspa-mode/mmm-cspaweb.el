;;; mmm-cspaweb.el --- MMM submode class for CSPAWeb programs derivate from mmm-web.el

;;; Commentary:

;; This file contains the definition of an MMM Mode submode class for
;; editing Cspaweb programs.

;;; Code:

(require 'mmm-compat)
(require 'mmm-vars)
(require 'mmm-auto)

(defvar mmm-cspaweb-section-tags
  '("@ " "@*"))

(defvar mmm-cspaweb-section-regexp
  (concat "^" (mmm-regexp-opt mmm-cspaweb-section-tags t)))

(defvar mmm-cspaweb-c-part-tags
  '("@c" "@>=" "@>+=" "@p"))

(defvar mmm-cspaweb-c-part-regexp
  (concat (mmm-regexp-opt mmm-cspaweb-c-part-tags t)))

(defun mmm-cspaweb-in-limbo (pos)
  "Check to see if POS is in limbo, ie before any cspaweb sections."
  (save-match-data
    (save-excursion
      (goto-char pos)
      (not (re-search-backward mmm-cspaweb-section-regexp nil t)))))

(defun mmm-cspaweb-verify-brief-c ()
  "Verify function for cspaweb-brief-c class.
Checks whether the match is in limbo."
  (not (mmm-cspaweb-in-limbo (match-beginning 0))))

(mmm-add-group
 'cspaweb
 `(
   (cspaweb-c-part
    :submode cspa-mode
    :front ,mmm-cspaweb-c-part-regexp
    :back ,mmm-cspaweb-section-regexp)
   (cspaweb-label
    :submode tex-mode
    :front "@<"
    :back "@>"
    :face mmm-comment-submode-face
    :insert ((?l cspaweb-label nil @ "@<" @ "@>")))
   (cspaweb-brief-c
    :submode cspa-mode
    :front "[^\\|]\\(|\\)[^|]"
    :front-match 1
    :front-verify mmm-cspaweb-verify-brief-c
;    :front-offset -1
    :back "[^\\|]\\(|\\)"
    :back-match 1
;    :back-offset 1
    :end-not-begin t
    :insert ((?| cspaweb-c-in-tex nil "|" @ "|")))
    (cspaweb-comment
     :submode tex-mode
     :front "/[*]"
     :back "[*]/"
     :face mmm-comment-submode-face)
))


;; (add-to-list 'mmm-mode-ext-classes-alist
;;                   '(plain-tex-mode "\\.w\\'" cspaweb))
;; (add-to-list 'mmm-mode-ext-classes-alist
;;                   '(latex-mode "\\.w\\'" cspaweb))
;; (add-to-list 'auto-mode-alist '("\\.w\\'" . tex-mode))

(provide 'mmm-cspaweb)

;;; mmm-cspaweb.el ends here