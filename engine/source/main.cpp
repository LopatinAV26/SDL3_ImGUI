#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <memory>
#include "core.hpp"

#include <podofo/podofo.h>

#include <string>
#include <stdexcept>
#include <iostream>

using namespace PoDoFo;
using namespace std;

void HelloWorld(const string_view& filename)
{
    // The document is written directly to filename while being created.
    PdfMemDocument document;

    // PdfPainter is the class which is able to draw text and graphics
    // directly on a PdfPage object.
    PdfPainter painter;

    // A PdfFont object is required to draw text on a PdfPage using a PdfPainter.
    // PoDoFo will find the font using fontconfig on your system and embed truetype
    // fonts automatically in the PDF file.
    PdfFont* font;

    try
    {
        // The PdfDocument object can be used to create new PdfPage objects.
        // The PdfPage object is owned by the PdfDocument will also be deleted automatically
        // by the PdfDocument object.
        // 
        // You have to pass only one argument, i.e. the page size of the page to create.
        // There are predefined enums for some common page sizes.
        auto& page = document.GetPages().CreatePage(PdfPageSize::A4);

        // Set the page as drawing target for the PdfPainter.
        // Before the painter can draw, a page has to be set first.
        painter.SetCanvas(page);

        // Create a PdfFont object using the font "Arial".
        // The font is found on the system using fontconfig and embedded into the
        // PDF file. If Arial is not available, a default font will be used.
        // 
        // The created PdfFont will be deleted by the PdfDocument.
        font = document.GetFonts().SearchFont("Arial");

        // If the PdfFont object cannot be allocated return an error.
        if (font == nullptr)
            throw runtime_error("Invalid handle");

        auto& metrics = font->GetMetrics();
        cout << "The font name is "<< metrics.GetFontName() << endl;
        cout << "The family font name is " << metrics.GetFontFamilyName() << endl;
        cout << "The font file path is " << metrics.GetFilePath() << endl;
        cout << "The font face index is " << metrics.GetFaceIndex() << endl;

        // Set the font as default font for drawing.
        // A font has to be set before you can draw text on
        // a PdfPainter.
        painter.TextState.SetFont(*font, 18);

        // You could set a different color than black to draw
        // the text.
        // 
        // painter.SetColor(1.0, 0.0, 0.0);

        // Actually draw the line "Hello World!" on to the PdfPage at
        // the position 2cm,2cm from the top left corner.
        // Please remember that PDF files have their origin at the
        // bottom left corner. Therefore we substract the y coordinate
        // from the page height.
        // 
        // The position specifies the start of the baseline of the text.
        // 
        // All coordinates in PoDoFo are in PDF units.
        painter.DrawText("ABCDEFGHIKLMNOPQRSTVXYZ", 56.69, page.GetRect().Height - 56.69);

        try
        {
            // Add also some non-ASCII characters (Cyrillic alphabet)
            painter.DrawText("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЬЫЭЮЯ", 56.69, page.GetRect().Height - 80);
        }
        catch (PdfError& err)
        {
            if (err.GetCode() == PdfErrorCode::InvalidFontData)
                cout << "WARNING: The matched font \"" << metrics.GetFontName() << "\" doesn't support cyrillic" << endl;
        }

        // Tell PoDoFo that the page has been drawn completely.
        // This required to optimize drawing operations inside in PoDoFo
        // and has to be done whenever you are done with drawing a page.
        painter.FinishDrawing();

        // Set some additional information on the PDF file.
        document.GetMetadata().SetCreator(PdfString("examplahelloworld - A PoDoFo test application"));
        document.GetMetadata().SetAuthor(PdfString("Dominik Seichter"));
        document.GetMetadata().SetTitle(PdfString("Hello World"));
        document.GetMetadata().SetSubject(PdfString("Testing the PoDoFo PDF Library"));
        document.GetMetadata().SetKeywords(vector<string>({ "Test", "PDF", "Hello World" }));

        // The last step is to close the document.
        document.Save(filename);
    }
    catch (PdfError&)
    {
        // All PoDoFo methods may throw exceptions
        // make sure that painter.FinishPage() is called
        // or who will get an assert in its destructor
        try
        {
            painter.FinishDrawing();
        }
        catch (...)
        {
            // Ignore errors this time
        }

        throw;
    }
}

auto core = std::make_unique<Core>();

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
	// Core *core = new Core();
	//*appstate = core;
	return core->Init();
};

SDL_AppResult SDL_AppIterate(void *appstate)
{
	// Core *core = static_cast<Core *>(appstate);
	return core->Iterate();
};

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	// Core *core = static_cast<Core *>(appstate);
	return core->ProcessEvent(event);
};

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	// Core *core = static_cast<Core *>(appstate);
	// delete core;
	// core = nullptr;
	// appstate = nullptr;
	SDL_Log("Application shutdown complete.");
};