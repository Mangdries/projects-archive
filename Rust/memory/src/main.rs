use std::io;
use std::io::Write;

use rand::Rng;

#[derive(Default)]
enum Values {
    #[default]
    Cherry,
    StawBerry,
    Grape,
    Orange,
    //Easy
    Mango,
    Apple,
    //Medium
    Banana,
    DragonFruit,
    None,
    //Hard
}

#[derive(Default)]
enum Difficulty {
    #[default]
    Easy,
    Medium,
    Hard,
}

#[derive(Default)]
enum Orientation {
    #[default]
    Down,
    Up,
}

#[derive(Default)]
struct Cards {
    difficulty: Difficulty,
    cards: Vec<Vec<(i32, Orientation)>>,
}

impl Cards {
    fn gen_cards(&mut self) {
        //Rows
        let rows;
        //Columns
        let columns;
        //Total amount of different card values
        let matches;
        match self.difficulty {
            Difficulty::Easy => {
                rows = 4;
                columns = 2;
                matches = 4;
            }

            Difficulty::Medium => {
                rows = 4;
                columns = 3;
                matches = 6;
            }

            Difficulty::Hard => {
                rows = 4;
                columns = 4;
                matches = 8;
            }
        }

        self.cards.clear();
        //To avoid repeats
        let mut used_cards = [0; 8];

        for x in 0..rows {
            for _ in 0..columns {
                loop {
                    let card = rand::rng().random_range(0..matches);
                    if used_cards[card] < 2 {
                        used_cards[card] += 1;
                        self.cards.push(Default::default());
                        self.cards[x].push(((card as i32), Orientation::Down));
                        break;
                    }
                }
            }
        }
    }

    fn print_cards(&self) {
        let max_col;
        match self.difficulty {
            Difficulty::Easy => max_col = 2,
            Difficulty::Medium => max_col = 3,
            Difficulty::Hard => max_col = 4,
        }

        let mut cols = 0;
        for row in self.cards.iter() {
            print!("{} |", cols + 1);
            for col in row.iter() {
                match col.1 {
                    Orientation::Up => match Self::to_values(col.0) {
                        Values::Cherry => print!("C|"),
                        Values::StawBerry => print!("S|"),
                        Values::Grape => print!("G|"),
                        Values::Orange => print!("O|"),
                        Values::Mango => print!("M|"),
                        Values::Apple => print!("A|"),
                        Values::Banana => print!("B|"),
                        Values::DragonFruit => print!("D|"),
                        _ => print!(" |"),
                    },
                    Orientation::Down => print!("?|"),
                }
            }

            println!("");

            cols += 1;
            if cols == max_col {
                break;
            };
        }
    }

    fn flip_card(&mut self, card: (String, String)) {
        let mut card_int = (
            card.0.parse::<usize>().unwrap(),
            card.1.parse::<usize>().unwrap(),
        );
        card_int.0 -= 1;
        card_int.1 -= 1;

        match self.cards[card_int.0][card_int.1].1 {
            Orientation::Down => self.cards[card_int.0][card_int.1].1 = Orientation::Up,
            Orientation::Up => self.cards[card_int.0][card_int.1].1 = Orientation::Down,
        }
    }

    fn compare(&mut self, card1: &(String, String), card2: &(String, String)) {
        let card1 = (
            card1.0.parse::<usize>().unwrap(),
            card1.1.parse::<usize>().unwrap(),
        );
        let card2 = (
            card2.0.parse::<usize>().unwrap(),
            card2.1.parse::<usize>().unwrap(),
        );

        if self.cards[card1.0][card2.1].0 == self.cards[card2.0][card2.1].0 {
            println!("Match!");

            self.cards[card1.0][card2.1].0 = 8;
            self.cards[card2.0][card2.1].0 = 8;
        }
    }

    fn hide_cards(&mut self) {
        for row in self.cards.iter_mut() {
            for c in row.iter_mut() {
                c.1 = Orientation::Down;
            }
        }
    }

    fn to_values(val: i32) -> Values {
        match val {
            0 => return Values::Cherry,
            1 => return Values::StawBerry,
            2 => return Values::Grape,
            3 => return Values::Orange,
            4 => return Values::Mango,
            5 => return Values::Apple,
            6 => return Values::Banana,
            7 => return Values::DragonFruit,
            _ => return Values::None,
        }
    }
}

fn menu() -> i32 {
    println!("Memory Game!");
    println!("1. Easy");
    println!("2. Medium");
    println!("3. Hard");
    println!("Enter your selection (1-3)");

    let mut input = String::new();

    loop {
        print!("> ");
        io::stdout().flush().unwrap();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read line");

        match input.as_str().trim() {
            "1" => return 1,
            "2" => return 2,
            "3" => return 3,
            _ => input.clear(),
        }
    }
}

fn main() {
    let mut cards: Cards = Default::default();
    match menu() {
        1 => cards.difficulty = Difficulty::Easy,
        2 => cards.difficulty = Difficulty::Medium,
        3 => cards.difficulty = Difficulty::Hard,
        _ => {}
    }

    cards.gen_cards();
    let mut flipped_cards = 0;
    let mut is_first_flip = true;
    let mut first_flip: (String, String) = (String::from(""), String::from(""));
    loop {
        cards.print_cards();
        let mut user_selection = (String::from(""), String::from(""));
        print!("X > ");
        io::stdout().flush().unwrap();
        io::stdin().read_line(&mut user_selection.0).unwrap();
        user_selection.0 = user_selection.0.trim().to_string();
        print!("Y > ");
        io::stdout().flush().unwrap();
        io::stdin().read_line(&mut user_selection.1).unwrap();
        user_selection.1 = user_selection.1.trim().to_string();

        cards.flip_card(user_selection.clone());

        flipped_cards += 1;
        if flipped_cards == 2 {
            cards.hide_cards();
            flipped_cards = 0;
        }

        match is_first_flip {
            true => {
                is_first_flip = false;
                first_flip = user_selection.clone();
            }
            false => {
                is_first_flip = true;
                cards.compare(&first_flip, &user_selection);
            }
        }
    }
}
