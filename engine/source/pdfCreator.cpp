#include "pdfCreator.hpp"
#include "tableCreator.hpp"

PdfCreator::PdfCreator()
{
}

PdfCreator::~PdfCreator()
{
    font = nullptr;
}

void PdfCreator::CreateTable()
{
    painter.SetCanvas(page);

    font = document.GetFonts().SearchFont("Arial");

    painter.TextState.SetFont(*font, 12);

    painter.DrawRectangle(MmToDot(5), MmToDot(5), MmToDot(287), MmToDot(200));

    painter.FinishDrawing();

    SaveDocument(pdfFileName);
}

void PdfCreator::SaveDocument(std::string_view fileName)
{
    document.Save(fileName);
}

double PdfCreator::MmToDot(double mm)
{
    constexpr double dot = 25.4 / 72.0; // 0.3528 mm
    return mm / dot;
}
