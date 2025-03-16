#include <stdio.h>

void createFile(const char *filename, const char *category, const char questions[][256], const char options[][4][100], const char answers[], int total) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error creating %s\n", filename);
        return;
    }

    printf("Writing %d questions to %s...\n", total, filename);
    for (int i = 0; i < total; i++) {
        fprintf(file, "%s\n", questions[i]);
        for (int j = 0; j < 4; j++) {
            fprintf(file, "%s\n", options[i][j]);
        }
        fprintf(file, "%c\n", answers[i]);
    }

    fclose(file);
    printf("%s created successfully!\n", filename);
}

int main() {
    // General Knowledge Questions
    const char general_questions[][256] = {
        "What is the capital of Nepal?", "Who is the first president of Nepal?",
        "Which country is known as the Land of Rising Sun?", "What is the national animal of Nepal?",
        "What is the currency of Japan?", "Which planet is known as the Red Planet?",
        "Who wrote 'Muna Madan'?", "What is the national flower of Nepal?",
        "Which is the longest river in Nepal?", "Who was the first king of unified Nepal?",
        "In which year did Nepal get its first constitution?", "What is the national bird of Nepal?",
        "How many players are there in a football team?", "What is the highest mountain in the world?",
        "Which festival is known as the festival of lights?", "Who is known as the Light of Asia?",
        "What is the smallest country in the world?", "What is the national language of Nepal?",
        "Which is the largest ocean on Earth?", "How many colors are there in the rainbow?"
    };
    const char general_options[][4][100] = {
        {"Kathmandu", "Pokhara", "Lalitpur", "Bhaktapur"},
        {"Ram Baran Yadav", "Bidya Devi Bhandari", "Pushpa Kamal Dahal", "Madan Bhandari"},
        {"China", "Japan", "India", "Thailand"},
        {"Cow", "Tiger", "Elephant", "Rhinoceros"},
        {"Yuan", "Baht", "Yen", "Rupee"},
        {"Venus", "Mars", "Jupiter", "Saturn"},
        {"Laxmi Prasad Devkota", "Bhanubhakta Acharya", "Bal Krishna Sama", "Parijat"},
        {"Lotus", "Sunflower", "Rhododendron", "Jasmine"},
        {"Koshi", "Gandaki", "Karnali", "Bagmati"},
        {"Prithvi Narayan Shah", "Tribhuwan", "Mahendra", "Birendra"},
        {"1950", "1947", "1959", "1962"},
        {"Peacock", "Danphe", "Parrot", "Eagle"},
        {"9", "10", "11", "11"},
        {"K2", "Everest", "Makalu", "Lhotse"},
        {"Dashain", "Tihar", "Holi", "Chhath"},
        {"Siddhartha Gautam", "Mahatma Gandhi", "Nelson Mandela", "Jawaharlal Nehru"},
        {"Monaco", "Maldives", "Vatican City", "Bhutan"},
        {"Nepali", "Hindi", "Sanskrit", "Newari"},
        {"Atlantic", "Indian", "Pacific", "Arctic"},
        {"5", "6", "7", "8"}
    };
    const char general_answers[] = {'a', 'a', 'b', 'a', 'c', 'b', 'a', 'c', 'a', 'a', 'c', 'b', 'd', 'b', 'b', 'a', 'c', 'a', 'c', 'd'};

    createFile("general.txt", "General Knowledge", general_questions, general_options, general_answers, 20);

    // Science Questions
    const char science_questions[][256] = {
        "What is the chemical symbol for water?", "What gas do plants absorb from the atmosphere?",
        "Which is the largest organ in the human body?", "Who discovered gravity?",
        "What is the powerhouse of the cell?", "Which planet has the most moons?",
        "What is the hardest natural substance?", "Which vitamin is produced in the human body from sunlight?",
        "What is the speed of light?", "Which gas makes up most of the Earth's atmosphere?",
        "What is the study of fossils called?", "What is the unit of electric current?",
        "Who invented the telephone?", "What is the chemical formula of table salt?",
        "What is the main component of Earth's core?", "What type of rock is marble?",
        "What is the freezing point of water in Fahrenheit?", "What is the smallest particle of an element?",
        "What is the boiling point of water in Celsius?", "Which gas is needed for fire to burn?"
    };
    const char science_options[][4][100] = {
        {"H2O", "O2", "CO2", "H2SO4"},
        {"Oxygen", "Nitrogen", "Carbon Dioxide", "Helium"},
        {"Liver", "Brain", "Skin", "Heart"},
        {"Isaac Newton", "Albert Einstein", "Galileo Galilei", "Nikola Tesla"},
        {"Mitochondria", "Ribosome", "Nucleus", "Golgi Apparatus"},
        {"Jupiter", "Saturn", "Earth", "Neptune"},
        {"Gold", "Diamond", "Iron", "Platinum"},
        {"Vitamin A", "Vitamin C", "Vitamin D", "Vitamin E"},
        {"300,000 km/s", "150,000 km/s", "450,000 km/s", "600,000 km/s"},
        {"Oxygen", "Nitrogen", "Carbon Dioxide", "Hydrogen"},
        {"Geology", "Biology", "Paleontology", "Archaeology"},
        {"Volt", "Ampere", "Watt", "Ohm"},
        {"Alexander Graham Bell", "Thomas Edison", "Nikola Tesla", "Albert Einstein"},
        {"NaCl", "KCl", "MgCl2", "CaCl2"},
        {"Iron", "Nickel", "Both Iron & Nickel", "Carbon"},
        {"Igneous", "Sedimentary", "Metamorphic", "Granite"},
        {"0°F", "32°F", "100°F", "212°F"},
        {"Electron", "Proton", "Neutron", "Atom"},
        {"100°C", "50°C", "200°C", "300°C"},
        {"Oxygen", "Nitrogen", "Carbon Dioxide", "Argon"}
    };
    const char science_answers[] = {'a', 'c', 'c', 'a', 'a', 'b', 'b', 'c', 'a', 'b', 'c', 'b', 'a', 'a', 'c', 'c', 'b', 'a', 'a', 'a'};

    createFile("science.txt", "Science", science_questions, science_options, science_answers, 20);

    // Technology Questions
    const char tech_questions[][256] = {
        "Who is known as the father of computers?",
        "Which programming language is known as the 'mother of all languages'?",
        "What does 'HTML' stand for?",
        "Who founded Microsoft?",
        "What does 'CPU' stand for?",
        "Which company created the Android operating system?",
        "What does 'RAM' stand for?",
        "Which of the following is an open-source operating system?",
        "Who is the CEO of Tesla as of 2025?",
        "What year was the first iPhone released?",
        "Which programming language is mainly used for web development?",
        "What is the full form of 'HTTP'?",
        "Which search engine is owned by Microsoft?",
        "What is the most commonly used database system?",
        "Which company owns the Windows operating system?",
        "Which programming language is used in AI and machine learning?",
        "What is the name of Apple's AI voice assistant?",
        "Which company developed the C programming language?",
        "What does 'SSD' stand for in computer storage?",
        "Which networking device is used to connect multiple devices in a LAN?"
    };

    const char tech_options[][4][100] = {
        {"Charles Babbage", "Alan Turing", "Ada Lovelace", "Bill Gates"},
        {"C", "Assembly", "Fortran", "Python"},
        {"HyperText Markup Language", "HighText Machine Learning", "Hyper Transfer Markup Logic", "None of the above"},
        {"Bill Gates", "Steve Jobs", "Mark Zuckerberg", "Elon Musk"},
        {"Central Processing Unit", "Computer Power Unit", "Central Processor Utility", "None of the above"},
        {"Google", "Apple", "Microsoft", "Samsung"},
        {"Random Access Memory", "Read-Only Memory", "Rapid Application Module", "Remote Access Mode"},
        {"Windows", "Linux", "MacOS", "iOS"},
        {"Elon Musk", "Tim Cook", "Sundar Pichai", "Jeff Bezos"},
        {"2005", "2007", "2010", "2012"},
        {"Python", "Java", "JavaScript", "C++"},
        {"HyperText Transfer Protocol", "High Tech Transfer Protocol", "Hyperlink Text Processing", "None of the above"},
        {"Bing", "Yahoo", "Google", "DuckDuckGo"},
        {"MySQL", "MongoDB", "PostgreSQL", "SQLite"},
        {"Microsoft", "Apple", "Google", "IBM"},
        {"C++", "Python", "JavaScript", "Swift"},
        {"Siri", "Alexa", "Cortana", "Google Assistant"},
        {"IBM", "Microsoft", "Bell Labs", "Google"},
        {"Solid State Drive", "Storage System Device", "Software Security Disk", "Speed System Data"},
        {"Router", "Switch", "Hub", "Modem"}
    };

    const char tech_answers[] = {
        'a', 'b', 'a', 'a', 'a', 'a', 'a', 'b', 'a', 'b',
        'c', 'a', 'a', 'a', 'a', 'b', 'a', 'c', 'a', 'b'
    };

    createFile("tech.txt", "Technology", tech_questions, tech_options, tech_answers, 20);

    return 0;

}