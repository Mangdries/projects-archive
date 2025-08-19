use std::io;
use std::io::{stdout, Write};

#[derive(PartialEq)]
enum Turn {
    Red,
    Yellow,
}

const YELLOW: &str = "Y";
const RED: &str = "R";
const EMPTY: &str = " ";

fn main() {
    let mut turn = Turn::Red;

    let mut board: [[String; 7]; 6] = Default::default();

    let mut winner = false;

    init_board(&mut board);

    while !winner {
        print_board(&board);
        update_board(&mut board, &mut turn);
        check_win(&board, &mut winner);
    }

    print_board(&board);

    match turn {
        Turn::Red => println!("Yellow wins!"),
        Turn::Yellow => println!("Red wins!"),
    }
}

fn init_board(board: &mut [[String; 7]; 6]) {
    for row in 0..6 {
        for col in 0..7 {
            board[row][col] = EMPTY.to_string();
        }
    }
}

fn print_board(board: &[[String; 7]; 6]) {
    for row in 0..6 {
        print!("{}", row + 1);
        print!("|");
        for col in 0..7 {
            if col != 6 {
                print!("{}|", board[row][col]);
            } else {
                print!("{}", board[row][col]);
            }
        }

        println!("|");
    }

    print!(" ");
    for col_num in 0..7 {
        print!(" {}", col_num + 1);
    }

    println!("\n");
}

fn update_board(board: &mut [[String; 7]; 6], turn: &mut Turn) {
    match turn {
        Turn::Red => println!("current turn: Red"),
        Turn::Yellow => println!("current turn: Yellow"),
    }

    print!("Your move: ");
    stdout().flush().unwrap();

    let mut position = String::new();

    io::stdin().read_line(&mut position).unwrap();

    if position.trim() == "Balls" || position.trim() == "balls" {
        print!("In yo jaws!");
    }

    let mut is_free = true;
    let position: i32 = match position.trim().parse() {
        Ok(position) => position,
        Err(_) => {
            is_free = false;
            -1
        }
    };

    if position >= 1 && position <= 7 && is_free == true {
        let mut y: i32 = 6;

        while y > 0 {
            if board[(y as usize) - 1][position as usize - 1] == EMPTY {
                break;
            } else {
                y -= 1;
            }
        }

        y -= 1;

        println!("{}", y);

        if y >= 0 {
            match turn {
                Turn::Red => board[y as usize][(position - 1) as usize] = RED.to_string(),
                Turn::Yellow => board[y as usize][(position - 1) as usize] = YELLOW.to_string(),
            }
        } else {
            is_free = false;
        }
    }

    println!("");
    if is_free == true {
        if *turn == Turn::Red {
            *turn = Turn::Yellow;
        } else {
            *turn = Turn::Red;
        }
    }
}

fn check_win(board: &[[String; 7]; 6], win: &mut bool) {
    //Vertical
    for i in 0..6 {
        for j in 0..3 {
            if board[j][i] == RED.to_string()
                && board[j + 1][i] == RED.to_string()
                && board[j + 2][i] == RED.to_string()
                && board[j + 3][i] == RED.to_string()
            {
                *win = true;
                break;
            } else if board[j][i] == YELLOW.to_string()
                && board[j + 1][i] == YELLOW.to_string()
                && board[j + 2][i] == YELLOW.to_string()
                && board[j + 3][i] == YELLOW.to_string()
            {
                *win = true;
                break;
            }
        }
    }

    //Horizontal
    for i in 0..6 {
        for j in 0..4 {
            if board[i][j] == RED.to_string()
                && board[i][j + 1] == RED.to_string()
                && board[i][j + 2] == RED.to_string()
                && board[i][j + 3] == RED.to_string()
            {
                *win = true;
                break;
            } else if board[i][j] == YELLOW.to_string()
                && board[i][j + 1] == YELLOW.to_string()
                && board[i][j + 2] == YELLOW.to_string()
                && board[i][j + 3] == YELLOW.to_string()
            {
                *win = true;
                break;
            }
        }
    }

    //Diagionals
    let mut y = 3;
    let mut hold_y = y;
    let mut x = 0;
    let mut hold_x = x;
    //let mut count = 0;

    //Leaning left
    loop {
        //count += 1;
        if (y as i32) - 3 >= 0 && x + 3 <= 6 {
            //println!("Checking. Y: {{{}}} X: {{{}}}", y, x);
            if board[y][x] == RED.to_string() && board[y-1][x+1] == RED.to_string() && board[y-2][x+2] == RED.to_string() && board[y-3][x+3] == RED.to_string() {
                *win = true;
                break;
            } else if board[y][x] == YELLOW.to_string() && board[y-1][x+1] == YELLOW.to_string() && board[y-2][x+2] == YELLOW.to_string() && board[y-3][x+3] == YELLOW.to_string() {
                *win = true;
                break;
            }

            y -= 1;
            x += 1;
        } else if y + 1 != 6 && x - 1 != 3 {
            //println!("Changing. Y: {{{}}} X: {{{}}}", y, x);
            if hold_y < 5 {
                hold_y += 1;
            } else {
                hold_x += 1;
            }

            y = hold_y;
            x = hold_x;
        } else {
            //println!("{count}\n");
            break;
        }
    }

    let mut y = 3;
    let mut hold_y = y;
    let mut x = 5;
    let mut hold_x = x;
    let mut count = 0;

    //Leaning right
    loop {
        println!("Y: {} X: {}", y, x);
        count += 1;
        if (y as i32) - 3 >= 0 && (x as i32) - 3 >= 0 {
            //println!("Checking. Y: {{{}}} X: {{{}}}", y, x);
            if board[y][x] == RED.to_string() && board[y-1][x-1] == RED.to_string() && board[y-2][x-2] == RED.to_string() && board[y-3][x-3] == RED.to_string() {
                *win = true;
                break;
            } else if board[y][x] == YELLOW.to_string() && board[y-1][x-1] == YELLOW.to_string() && board[y-2][x-2] == YELLOW.to_string() && board[y-3][x-3] == YELLOW.to_string() {
                *win = true;
                break;
            }

            y -= 1;
            x -= 1;
        } else if y + 1 != 6 && x + 1 != 2 {
            //println!("Valid");
            //println!("Changing. Y: {{{}}} X: {{{}}}\n", y, x);
            if hold_y < 5 {
                hold_y += 1;
            } else {
                hold_x -= 1;
            }

            y = hold_y;
            x = hold_x;
        } else {
            println!("{count}\n");
            break;
        }
    }
}
