use std::io;
use std::io::Write;

fn print_grid(tries: i32, answer: &String) {
    static mut PARTS: [&str; 3] = [" ", " ", " "];

    unsafe {
        match tries {
            1 => PARTS[0] = "[ ]",
            2 => PARTS[1] = "|",
            3 => PARTS[2] = "/\\",
            _ => {}
        }

        println!("-----|");
        println!("|   {}", PARTS[0]);
        println!("|    {}", PARTS[1]);
        println!("__   {}", PARTS[2]);
        println!("{answer}");
    }
}

fn main() {
    let words = [
        "Syntax",
        "Bread",
        "Range",
        "Along",
        "Video",
        "Seattle",
        "Pasta",
        "Base",
        "Dialogue",
        "Blameworthy",
        "Space",
        "Copyright",
        "Fridge",
        "Bake",
        "Based",
        "Bee",
    ];
    
    let answer = words[rand::random_range(0..words.len())];
    let mut answer_output = String::new();

    for _ in 0..answer.len() {
        answer_output.push_str(" ");
    }

    let mut attempts = 0;
    let mut input = String::new();

    while attempts < 3 {
        input.clear();
        print!("> ");
        io::stdout().flush().unwrap();
        io::stdin().read_line(&mut input).unwrap();
        input = input.trim().to_string();

        if input.len() == 1 && !input.contains(['1', '2', '3', '4', '5', '6', '7', '8', '9', '0']) {
            if !answer.to_lowercase().contains(&input.to_lowercase()) {
                attempts += 1;
            } else {
                if let Some(_) = answer.find(&input) {
                    let ch = input.chars().next().unwrap();
                    for (i, c) in answer.chars().enumerate() {
                        if c == ch {
                            answer_output.replace_range(i..i + 1, &input);
                        }
                    }
                } else if let Some(_) = answer.find(&input.to_uppercase()) {
                    let ch = input.to_uppercase().chars().next().unwrap();
                    for (i, c) in answer.chars().enumerate() {
                        if c == ch {
                            answer_output.replace_range(i..i + 1, &input);
                        }
                    }
                }

                if !answer_output.contains(" ") {
                    println!("You won!");
                    break;
                }
            }
        }

        print_grid(attempts, &answer_output);
        io::stdout().flush().unwrap();
    }

    if attempts == 3 {
        println!("The correct answer was {}", answer);
    }
}
