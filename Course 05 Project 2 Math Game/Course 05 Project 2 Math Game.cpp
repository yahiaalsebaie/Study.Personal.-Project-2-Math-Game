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
    int PlayerAnswer = 0;
    int CorrectAnswer = 0;
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
//bool IsRightAnswer(stQuiz& Quiz, short QIndex)
//{
//    return  Quiz.QuestionsList[QIndex].PlayerAnswer == Quiz.QuestionsList[QIndex].CorrectAnswer;
//}
bool IsRightAnswer(const stQuestion& q)
{
    return  q.PlayerAnswer == q.CorrectAnswer;
}
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
        break;
    case Med:
        Question.Number1 = RandomNumber(10, 100);
        Question.Number2 = RandomNumber(10, 100);
        break;
    case Hard:
        Question.Number1 = RandomNumber(99, 1000);
        Question.Number2 = RandomNumber(99, 1000);
        break;
    }
    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
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
string GetOperationName(enOperationType Op)
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
bool IsPass(const stQuiz& Quiz)
{
    return Quiz.CountCorrectAnswers >= Quiz.CountWrongAnswers;
}
void AskQuestion(stQuiz& Quiz, short QIndex)
{
    int PlayerAnswer = 0;

    cout << Quiz.QuestionsList[QIndex].Number1 << " " << GetOperationName(Quiz.QuestionsList[QIndex].OpType) << " ";
    cout << Quiz.QuestionsList[QIndex].Number2 << " = ";
    cin >> PlayerAnswer;
    Quiz.QuestionsList[QIndex].PlayerAnswer = PlayerAnswer;

}
//void UpdateScore(stQuiz& Quiz, short QIndex)
//{
//    if (Quiz.QuestionsList[QIndex].IsRightAnswer)
//    {
//        Quiz.CountCorrectAnswers++;
//        cout << "\nRight Answer :) \n---------------\n\n";
//
//    }
//    else
//    {
//        Quiz.CountWrongAnswers++;
//        cout << "\nWrong Answer :( \nThe Right Answer Is [" << Quiz.QuestionsList[QIndex].CorrectAnswer << "].\n----------------------------\n\n";
//    }
//}
void UpdateScore(stQuiz& Quiz, bool isRight)
{
    (isRight) ? Quiz.CountCorrectAnswers++ : Quiz.CountWrongAnswers++;
}
void PrintAnswerResult(const stQuiz Quiz, bool isRight, short QIndex)
{
    if (isRight)
        cout << "\nRight Answer :) \n---------------\n\n";
    else
        cout << "\nWrong Answer :( \nThe Right Answer Is [" << Quiz.QuestionsList[QIndex].CorrectAnswer << "].\n----------------------------\n\n";
}
void GenerateQuizQuestions(stQuiz& Quiz)
{
    //stQuestion Question;

    for (short QIndex = 0; QIndex < Quiz.HowManyQuestions; QIndex++)
    {
        cout << "Question [" << QIndex + 1 << "/" << Quiz.HowManyQuestions << "].\n";

        Quiz.QuestionsList[QIndex] = GenerateQuestion(Quiz.QuizLevel, Quiz.OpType);

        AskQuestion(Quiz, QIndex);

        // Quiz.QuestionsList[QIndex].IsRightAnswer = IsRightAnswer(Quiz, QIndex);
        Quiz.QuestionsList[QIndex].IsRightAnswer = IsRightAnswer(Quiz.QuestionsList[QIndex]);

        //UpdateScore(Quiz, QIndex);
        UpdateScore(Quiz, Quiz.QuestionsList[QIndex].IsRightAnswer);

        PrintAnswerResult(Quiz, Quiz.QuestionsList[QIndex].IsRightAnswer, QIndex);

        SetScreenColor(Quiz.QuestionsList[QIndex].IsRightAnswer);

    }
}
string GetPassMessage(bool isPass)
{
    if (isPass)
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
string GetOperationSymbol(enOperationType OpType)
{
    string arrQL[5]{ "Addition +" , "Subtraction -", "MultiPlay *","Divide /","Mix +-*/" };
    return arrQL[OpType - 1];
}
void ShowFinalGameResults(stQuiz Quiz)
{
    Quiz.IsPass = IsPass(Quiz);

    cout << Tabs() << "----------------------[Quiz Results]--------------------------\n";
    cout << Tabs(6) << GetPassMessage(Quiz.IsPass) << endl;
    cout << Tabs() << "--------------------------------------------------------------\n";
    cout << Tabs() << "Number of Questions : " << Quiz.HowManyQuestions << endl;
    cout << Tabs() << "Questions Level : " << GetQuestionLevelText(Quiz.QuizLevel) << endl;
    cout << Tabs() << "Operations Type : " << GetOperationSymbol(Quiz.OpType) << endl;
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