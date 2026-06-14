
#include <iostream>
#include <string>
using namespace std;

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Divide = 4, opMix = 5 };

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    enOperationType OpType;
    enQuestionsLevel QuestionLevel;
    bool AnswerResult = false;

};
struct stQuiz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions = 0;
    enOperationType OpType;
    enQuestionsLevel QuestionLevel;
    short WrongAnswersCount = 0;
    short RightAnswersCount = 0;
    bool IsPass = false;
};
string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case Add:
        return "+";
    case Sub:
        return "-";
    case Mult:
        return "x";
    case Divide:
        return "/";
    default:
        return "Mix";
    }
}
string GetQuestionLevelText(enQuestionsLevel QL)
{
    string arrQuestionsLevel[4]{ "Easy" , "Med", "Hard" ,"Mix" };
    return arrQuestionsLevel[QL - 1];
    /* switch (QL)
     {
     case Easy: return "Easy";
     case Med:  return "Medium";
     case Hard: return "Hard";
     case Mix: return "Mixed";
     default: return "Level";
     }*/
}

int RandomNumber(int From, int To)
{
    int random = rand() % (To - From + 1) + From;
    return random;
}

int ReadPositiveNumber(string Message)
{
    int Number = 0;
    do
    {
        cout << Message;
        cin >> Number;
    } while (Number <= 0);

    return Number;
}

int ReadNumberInRange(int From, int To)
{
    int Number = 0;
    do
    {
        cin >> Number;
        if (Number < From || Number > To)
            cout << "\nInvalid Input!\n";
    } while (Number < From || Number > To);

    return Number;
}
int ReadNumberInRange(int From, int To, string Message, string InValidInputMessage = "Enter a Valid Value : ")
{
    int Number = 0;
    do
    {
        cout << Message;
        cin >> Number;
        if (Number < From || Number > To)
        {
            cout << "\nInvalid Input!\n";
            cout << InValidInputMessage;
        }
    } while (Number < From || Number > To);

    return Number;
}
string Tabs(short NumberOfTabs = 3)
{
    string tabs = "";
    for (short i = 1; i <= NumberOfTabs; i++)
        tabs += "\t";
    return tabs;
}

enOperationType GetRandomOperationType()
{
    short Op = RandomNumber(1, 4);
    return (enOperationType)Op;
}
int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case Add: return Number1 + Number2;
    case Sub: return Number1 - Number2;
    case Mult: return Number1 * Number2;
    case Divide: return Number1 / Number2;
    default:  return Number1 + Number2;
    }
}
stQuestion  GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
    {
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    }
    if (OpType == enOperationType::opMix)
    {
        OpType = GetRandomOperationType();
    }
    Question.OpType = OpType;

    switch (QuestionLevel)
    {
    case Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case Med:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }
    return Question;
}
void GenerateQuizQuestions(stQuiz& Quiz)
{

    for (short Question = 0; Question < Quiz.NumberOfQuestions; Question++)
    {
        Quiz.QuestionList[Question] = GenerateQuestion(Quiz.QuestionLevel, Quiz.OpType);
    }

}

void ShowGameOverScreen()
{
    cout << Tabs() << "--------------------------------------------------------------\n";
    cout << Tabs(6) << "G a m e  O v e r \n";
    cout << Tabs() << "--------------------------------------------------------------\n";
}

string PrintIsPass(stQuiz Quiz)
{
    if (Quiz.IsPass)
    {
        system("color 2F"); //Green
        return "Passed ^_~";
    }
    else
    {
        system("color 4F"); //Red
        return   "Failed :(";
    }
}
void ShowFinalGameResults(stQuiz Quiz)
{

    cout << Tabs() << "----------------------[Quiz Results]--------------------------\n";
    cout << Tabs(6) << PrintIsPass(Quiz) << endl;
    cout << Tabs() << "--------------------------------------------------------------\n";
    cout << Tabs() << "Number of Questions : " << Quiz.NumberOfQuestions << endl;
    cout << Tabs() << "Questions Level : " << GetQuestionLevelText(Quiz.QuestionLevel) << endl;
    cout << Tabs() << "Operations Type : " << GetOpTypeSymbol(Quiz.OpType) << endl;
    cout << Tabs() << "Number of Right Answers : " << Quiz.RightAnswersCount << endl;
    cout << Tabs() << "Number of Wrong Answers : " << Quiz.WrongAnswersCount << endl;
    cout << Tabs() << "--------------------------------------------------------------\n";


}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}
void PrintTheQuestion(stQuiz Quiz, short QuestionNumber)
{
    cout << endl;
    cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestions << "].\n\n";
    cout << Quiz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quiz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quiz.QuestionList[QuestionNumber].OpType);
    cout << "\n========\n";

}
void SetScreenColor(bool isRight)
{
    if (isRight)
        system("color 2F"); // Green 
    else
    {
        system("color 4F"); // Red
        cout << "\a";
    }
}
void CorrectTheQuestionAnswer(stQuiz& Quiz, short QuestionNumber)
{
    if (Quiz.QuestionList[QuestionNumber].PlayerAnswer == Quiz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = true;
        cout << "The Answer is Correct ^_~\n\n";
        Quiz.RightAnswersCount++;
    }
    else
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = false;
        cout << "\nWrong Answer :(\n--> Correct answer is [" << Quiz.QuestionList[QuestionNumber].CorrectAnswer << "].\n\n";
        Quiz.WrongAnswersCount++;
    }
    cout << endl;
    SetScreenColor(Quiz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuiz& Quiz)
{
    int Answer = 0;
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quiz, QuestionNumber);

        cin >> Answer;
        Quiz.QuestionList[QuestionNumber].PlayerAnswer = Answer;

        CorrectTheQuestionAnswer(Quiz, QuestionNumber);
    }
    Quiz.IsPass = (Quiz.RightAnswersCount >= Quiz.WrongAnswersCount);
}
void PlayMathGame()
{
    stQuiz Quiz;
    Quiz.NumberOfQuestions = ReadNumberInRange(1, 10, "How Many Questions do you want to answer ? >> ");
    Quiz.QuestionLevel = (enQuestionsLevel)ReadNumberInRange(1, 4, "Enter Questions Level [Easy = 1, Med = 2, Hard = 3, Mix = 4] >> ");
    Quiz.OpType = (enOperationType)ReadNumberInRange(1, 5, "Enter Operations Type [Add = 1,Sub = 2,Multi = 3,Divide = 4,Mix = 5] >> ");

    GenerateQuizQuestions(Quiz);
    AskAndCorrectQuestionListAnswers(Quiz);

    ShowGameOverScreen();

    ShowFinalGameResults(Quiz);
}
void StartGame()
{

    char PlayAgain = 'y';
    do
    {

        ResetScreen();
        PlayMathGame();


        cout << "\nDo You want to play again ? [Y/N] : ";
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');

}
int main()
{

    srand((unsigned)time(NULL));

    StartGame();

}

