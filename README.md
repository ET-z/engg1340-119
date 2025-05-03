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
This game requires the ncurses library to run properly!
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
GOAL: Outlast the dealer. 
Choose the difficulty of the AI when starting the game, there are 3 modes to be chosen from.
    Dumb AI: Always shoots the player
    Risk aware: if there is more than 40% chance of a live shell, it will shoot the player
    Scope aware: knows the order of the shells and will act accordingly
Controls: 
    Use the arrow keys to navigate your inventory
    E/e -> Pick up and use an item
    Enter/ Space -> Initiate shooting, choose 1 to shoot yourself, choose 2 to shoot The Dealer.



> [!NOTE]
> For the best experience, we recommend playing the official [soundtrack](https://www.youtube.com/watch?app=desktop&v=tZmq052Cf_Q&ab_channel=Tobythefloof) in the background!

### Items

Apple → +20 HP
Knife → Double damage! (20 -> 40 damage)
Beer → Discard the current shell
Magnifying Glass → See if the next shell is live
Handcuff → Skip the dealer's turn
To pick up item: press E/e

> [!TIP]
> Helpful advice for doing things better or more easily.

---

## Disclaimers / Additional information

> [!CAUTION]
> Due to the game not being able to run on MacOS,
> developers on the system had to commit and push every miniscule change,
> then pull the remote repository to the linux server to debug.
> Thus, there are so many commits without proper descriptions.
>

> This game is not infringing on any of the rights of the original Buckshot Roulette according to Fair Use
> Future improvements: More items available, double player mode and smarter AI algorithm
---

## About our project

### Random events

Our shell generation function utilize the rand(time(0)) function to generate a random seed. We use the random_shuffle function to generate a sequence of the shells.
Our items are also randomly generated and placed.

### Data structure for storin data / Dynamic memory management

Vectors to store items and shells as well as pointers are used (Working with ncurses requires initiating multiple WINDOW * pointers). The game window is properly cleared and deleted when you exit the game.

### File I/O

Drawing of the player and The Dealer is handled by the fin function, ASCII art of the characters are placed inside .txt files and drew to the screen row by row.

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
