#include <iostream>
#include <string>
using namespace std;

enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuestion {
    short Number1 = 0;
    short Number2 = 0;
    enOperationType OpType;
    enQuestionLevel QuestionLevel;
    short PlayerAnswer = 0;
    short CorrectAnswer = 0;
    bool IsRightAnswer = false;
};
struct stQuiz {
    stQuestion QuestionsList[100];
    short HowManyQuestions = 0;
    enOperationType OpType;
    enQuestionLevel QuizLevel;
    short CountWrongAnswers = 0;
    short CountCorrectAnswers = 0;
    bool IsPass = false;
};

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
int ReadNumberInRange(int From, int To, string Message, string InValidInputMessage = "")
{
    int Number = 0;
    do
    {
        cout << Message;
        cin >> Number;
        if (Number < From || Number > To)
        {
            cout << "\nInvalid Input! Enter In Range [" << From << " to " << To << "].\n";

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

void ShowGameOverScreen()
{
    cout << Tabs() << "--------------------------------------------------------------\n";
    cout << Tabs(6) << "G a m e  O v e r \n";
    cout << Tabs() << "--------------------------------------------------------------\n";
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}
int SimpleCalculator(int Number1, int Number2, enOperationType Op)
{
    ;
    switch (Op)
    {
    case Add: return Number1 + Number2;
    case Sub: return Number1 - Number2;
    case Mul: return Number1 * Number2;
    case Div: return Number1 / Number2;
    default:  return Number1 + Number2;
    }
}
bool IsRightAnswer(stQuiz& Quiz, short QIndex)
{
    stQuestion Question;
    return  Quiz.QuestionsList[QIndex].PlayerAnswer == Quiz.QuestionsList[QIndex].CorrectAnswer ? Quiz.QuestionsList[QIndex].IsRightAnswer = true : false;
}
//bool IsRightAnswer(stQuestion Question)
//{
//    return  Question.PlayerAnswer == Question.CorrectAnswer ? Question.IsRightAnswer = true : false;
//}
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (OpType == enOperationType::MixOp)
        OpType = (enOperationType)RandomNumber(1, 4);
    Question.OpType = OpType;

    if (QuestionLevel == enQuestionLevel::Mix)
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    Question.QuestionLevel = QuestionLevel;

    switch (Question.QuestionLevel)
    {
    case Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        return Question;
    case Med:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        return Question;
    case Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        return Question;

    }
    return Question;
}
void SetScreenColor(bool isRight)
{
    if (isRight) system("color 2F");
    else {
        system("color 4f");
        cout << "\a";
    }
}
string GetOperationSymbol(enOperationType Op)
{
    switch (Op)
    {
    case Add: return "+";
    case Sub: return "-";
    case Mul:return "*";
    case Div: return "/";
    default: return "Mix";
    }
}
bool IsPass(stQuiz& Quiz)
{
    return Quiz.CountCorrectAnswers >= Quiz.CountWrongAnswers ? Quiz.IsPass = true : Quiz.IsPass = false;
}
void GenerateQuizQuestions(stQuiz& Quiz)
{
    int PlayerAnswer = 0;

    for (short QIndex = 0; QIndex < Quiz.HowManyQuestions; QIndex++)
    {
        cout << "Question [" << QIndex + 1 << "/" << Quiz.HowManyQuestions << "].\n";

        Quiz.QuestionsList[QIndex] = GenerateQuestion(Quiz.QuizLevel, Quiz.OpType);

        cout << Quiz.QuestionsList[QIndex].Number1 << endl;
        cout << Quiz.QuestionsList[QIndex].Number2 << " " << GetOperationSymbol(Quiz.QuestionsList[QIndex].OpType);
        cout << "\n====\n";
        cin >> PlayerAnswer;
        Quiz.QuestionsList[QIndex].PlayerAnswer = PlayerAnswer;

        Quiz.QuestionsList[QIndex].IsRightAnswer = IsRightAnswer(Quiz, QIndex);
        if (Quiz.QuestionsList[QIndex].IsRightAnswer)
        {
            Quiz.CountCorrectAnswers++;
            cout << "\nRight Answer :) \n---------------\n\n";

        }
        else
        {
            Quiz.CountWrongAnswers++;
            cout << "\nWrong Answer :( \nThe Right Answer Is [" << Quiz.QuestionsList[QIndex].CorrectAnswer << "].\n----------------------------\n\n";
        }

        SetScreenColor(Quiz.QuestionsList[QIndex].IsRightAnswer);

    }
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
string GetQuestionLevelText(enQuestionLevel QL)
{
    string arrQL[4]{ "Easy" , "Med", "Hard" ,"Mix" };
    return arrQL[QL - 1];
}
string GetOpTypeSymbol(enOperationType OpType)
{
    string arrQL[5]{ "Addition +" , "Subtraction -", "MultiPlay *","Divide /","Mix +-*/" };
    return arrQL[OpType - 1];
}
void ShowFinalGameResults(stQuiz Quiz)
{
    IsPass(Quiz);

    cout << Tabs() << "----------------------[Quiz Results]--------------------------\n";
    cout << Tabs(6) << PrintIsPass(Quiz) << endl;
    cout << Tabs() << "--------------------------------------------------------------\n";
    cout << Tabs() << "Number of Questions : " << Quiz.HowManyQuestions << endl;
    cout << Tabs() << "Questions Level : " << GetQuestionLevelText(Quiz.QuizLevel) << endl;
    cout << Tabs() << "Operations Type : " << GetOpTypeSymbol(Quiz.OpType) << endl;
    cout << Tabs() << "Number of Right Answers : " << Quiz.CountCorrectAnswers << endl;
    cout << Tabs() << "Number of Wrong Answers : " << Quiz.CountWrongAnswers << endl;
    cout << Tabs() << "--------------------------------------------------------------\n";


}
void PlayMathGame()
{
    stQuiz Quiz;
    Quiz.HowManyQuestions = (short)ReadNumberInRange(1, 10, "How Many Questions Do you Want to Answer ? ->> ");
    Quiz.QuizLevel = (enQuestionLevel)ReadNumberInRange(1, 4, "Enter Questions Level  { Easy = 1, Med = 2, Hard = 3, Mix = 4 } ->> ");
    Quiz.OpType = (enOperationType)ReadNumberInRange(1, 5, "Enter Operation Type { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5 } ->> ");

    GenerateQuizQuestions(Quiz);

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

int main() {
    srand((unsigned)time(NULL));

    StartGame();
    return 0;
}