#pragma once

#include <memory>
#include <podofo/podofo.h>
// #include <SDL3/SDL.h>

class Table;

class PdfCreator
{
public:
    PdfCreator();
    ~PdfCreator();
    void CreateTable();
    void SaveDocument(std::string_view fileName);

private:
    double MmToDot(double mm);

    PoDoFo::PdfMemDocument document;

    PoDoFo::PdfPage &page = document.GetPages().CreatePage(
        PoDoFo::PdfPage::CreateStandardPageSize(PoDoFo::PdfPageSize::A4, true));

    PoDoFo::PdfPainter painter;
    PoDoFo::PdfFont *font{nullptr};

    std::string pdfFileName{"PDF_Test"};

    PoDoFo::Rect prect;

    std::unique_ptr<Table> table;
};