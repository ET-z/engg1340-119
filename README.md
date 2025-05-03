# engg1340-119 - Buckshot Roulette

> [!CAUTION]
> The game does not run on MacOS due to lack of wide-character version of ncurses!

---

## Members:

- @ET-z **Enkhtushig Zolzaya** - 3036294578
- @DuskNova **Tianhong Gao** - 3036459300
- @tmng **Tran Minh Nguyen** - 3036384892
- @tue-nhi **Nguyen Tue Nhi** - 3036364517
- @kk212371 **Kong Tianxi** - 3036392461
- @Maggie-maoyiqi **Mao Yiqi** - 3036291186

---

## Introduction

> Long last, we arrive at the final showdown.
> No more defibrillators.
> No more blood transfusions.
> Now, me and you, we are dancing on the edge of life and death.

Buckshot Roulette is a 2023 indie tabletop horror video game developed and published by Estonian game developer Mike Klubnika on itch.io, which gained lots of attention and traction among gamers. This is a remake of this game using C++.

The game feature a mysterious figure, "The Dealer", of whom we play a modified Russian Roulette. Player and the dealer only has 100 health, and each round will have 9 shells (live or blank). This is a shootout until one man dies, and the game will continue to reload if both are alive. Items are included in the game, but use them wisely and you might stand a chance.

---

## How to run the game

To compile the game and immediately run it, enter the following command into your Linux terminal:

```
make run
```

> [!CAUTION]
> Make sure your terminal is big enough to run the game! 
> Resizing the screen, lowering the font size in your terminal or changing to another terminal are proven methods. The screen size is set so that the UX is optimized

---

## How to play the game

Refer to the tutorial (t) on the initial menu screen.


> [!NOTE]
> For the best experience, we recommend playing the official [soundtrack](https://www.youtube.com/watch?app=desktop&v=tZmq052Cf_Q&ab_channel=Tobythefloof) in the background!

### Items

> [!TIP]
> Helpful advice for doing things better or more easily.

---

## Disclaimers / Additional information

> [!CAUTION]
> Due to the game not being able to run on MacOS,
> developers on the system had to commit and push every miniscule change,
> then pull the remote repository to the linux server to debug.
> Thus, there are so many commits without proper descriptions.

---

## About our project

### Random events

- Showcase random event functions and explain them

### Data structure for storin data / Dynamic memory management

- Showcase our use of vectors and windows, etc.

### File I/O

- Talk about how our game utilizes file I/O for ASCII

```
     AAAAAAA       AAAAAAA
    AA    AS          AA   AA
   AA   AM              AZ  AA
   A   A                 A   A
  AZ  A                 A  ZA
   AA  AA              AA   AA
    AW   AAAAAAAAAAAAAA   WA
      AA                 AA
      AA                 AA
      AA                 AA
      AA  AAAA     AAAA  AA
      A  AAAAAA   AAAAAA  A
      AA  AAAA     AAAA AA
        AA             AA
          AAAAAAAAAAAAA
```

```
           AAACCACCCCBAAAAAD
        AAABSPPRPPSPQSSSKCBAAAA
     HSOKOXTMNTSSSSSSL KKQQSSSSSE
    YKK       SKOSPQKZS       GSSG
    EKS        KSWASUK        KLONK
   MPU         KSJBSSK        SY SS
  XDFS S       RVLJCHSKW      MAAAAA
 AASEAERNSSSWUKSCCCCPSKKPSP SAABR TAS
 S    KJAEIFRSN KCCACSTWSSDAAI      K
 M    X  WKIJFDO      IJOCG Z KCS  TS
 GJ SE  CQS   ZRLGQMLMRT  X MCSZ   OS
 MEI XSC  DG RK S   W  I  IJ YPGU SSR
  USMK  C C  CC UC OD  C J CJK  SSSS
    SSKG   D C  YH  C  XZC   X KKSS
     JPRHKKY  H   D ZPW  KY JJQSS
       WCSOSBFS        WMCOQCSU
           SUBAAACCAAAAAGRS
```
