.arm

.section .patch_ShorterAnimationFail
.global patch_ShorterAnimationFail
patch_ShorterAnimationFail:
  b 0x5B1870

.section .patch_ShorterAnimationOpenOne
.global patch_ShorterAnimationOpenOne
patch_ShorterAnimationOpenOne:
  .float 0.001

.section .patch_ShorterAnimationOpenTwo
.global patch_ShorterAnimationOpenTwo
patch_ShorterAnimationOpenTwo:
  .float 0.001

.section .patch_ShorterAnimationOpenThree
.global patch_ShorterAnimationOpenThree
patch_ShorterAnimationOpenThree:
  .float 0.001

.section .patch_ShorterAnimationOpenFour
.global patch_ShorterAnimationOpenFour
patch_ShorterAnimationOpenFour:
  .float 0.001

.section .patch_ShorterAnimationOpenFive
.global patch_ShorterAnimationOpenFive
patch_ShorterAnimationOpenFive:
  .float 0.001

.section .patch_ShorterAnimationOpenSix
.global patch_ShorterAnimationOpenSix
patch_ShorterAnimationOpenSix:
  .float 0.001
