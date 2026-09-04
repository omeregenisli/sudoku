# Binary Sudoku (C Console Game)

A grid-based puzzle game implemented in C, merging traditional Sudoku structure with dynamic piece placement and binary score evaluation.

Developed as a group project for **EED 1005 - Introduction to Programming** at Dokuz Eylül University.

---

## 📊 Project Presentation & Documentation
* 📑 **[View Project Presentation (PDF)](Project-Presentation.pdf)** *(Recommended — Overview of mechanics, piece layout & architecture)*
* 📝 **[View Progress Report (PDF)](Project-Report.pdf)** *(Detailed algorithm explanations, flowcharts & team task logs)*

---

## 🎮 Game Overview & Rules
* **Grid Layout:** Played on a 9x9 matrix organized into nine 3x3 sub-grids.
* **Piece Mechanics:** 10 distinct geometric piece variations generate sequentially at random.
* **Line & Block Clears:** Placing pieces to complete any full row, column, or 3x3 square clears those cells.
* **Binary Scoring:** Cells cleared in rows, columns, or blocks are evaluated as binary numbers (0s and 1s) and converted into base-10 integer score increments.
* **Game Over:** Triggers when the board contains no valid coordinates remaining to place the active piece.

---

## 🛠️ My Role & Algorithmic Contributions
* **Placement & Collision Detection:** Authored the core routines (`place_piece`, `valid_invalid`) that check boundaries, validate coordinate inputs, and prevent tile collisions.
* **Clear & Evaluation Logic:** Developed logic within `check_clear` to detect completed rows, columns, and 3x3 blocks and manage matrix clearing.
* **Input & Edge-Case Handling:** Corrected coordinate parsing errors and prevented edge-case grid out-of-bounds exceptions.

---

## 👥 Contributors
* Ömer Ege NİŞLİ
* İsmail ÖZTÜRK
* Mehmetcan KIRCA
* Muhammet Emre AY
* Zeynep SEYHUN
* Halil Ilgaz KESKİN
* Yiğithan YILDIRIM

*Course Lecturer: Öğr. Gör. Dr. Özlem ÖZTÜRK*
