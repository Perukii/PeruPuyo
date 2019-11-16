
#define peruSetColor(CR,PRGB) cairo_set_source_rgba(CR, PRGB.r, PRGB.g, PRGB.b, PRGB.a)

class pRGB{
public:
    double
        r = 0,
        g = 0,
        b = 0,
        a = 1
    ;
    pRGB(double _r = 0, double _g = 0, double _b = 0, double _a = 1):r(_r), g(_g), b(_b), a(_a){};
};

void peruDrawImage(cairo_t * cr, const char * file){
    cairo_surface_t * image;

    image = cairo_image_surface_create_from_png(file);
    cairo_set_source_surface(cr, image, 10, 10);
    cairo_paint(cr);
}

void peruDrawRect(cairo_t * cr, double x, double y, double w, double h, pRGB col=pRGB(0,0,0,1)){
    peruSetColor(cr,col);
    cairo_rectangle(cr, x, y, w, h);;
    cairo_fill(cr);
}


class peruText{
private:
    cairo_glyph_t* glyphs = NULL;
    int glyph_count;
    cairo_text_cluster_t* clusters = NULL;
    int cluster_count;
    cairo_text_cluster_flags_t clusterflags;
    cairo_scaled_font_t * scaled_face;



public:
    const char * text = "";
    double 
        strokeSize = 0;

    pRGB
        textCol,
        strokeCol
    ;

    peruText(const char * _text = "", pRGB _textCol = pRGB(0,0,0,1)){
        text = _text;
        textCol = _textCol;
        strokeCol = textCol;
    }



    void draw(cairo_t * cr, double x = 0, double y = 0, double fontSize = 10){
        cairo_set_font_size(cr, fontSize);
        scaled_face = cairo_get_scaled_font(cr);

        auto stat = cairo_scaled_font_text_to_glyphs(scaled_face, x, y, text, strlen(text), &glyphs, &glyph_count, &clusters, &cluster_count,
                &clusterflags);
        
        if(stat != CAIRO_STATUS_SUCCESS)return;

        // text paints on bottom line
        cairo_translate(cr, 0, fontSize);

        // draw each cluster
        int glyph_index = 0;
        int byte_index = 0;

        for (int i = 0; i < cluster_count; i++) {
            cairo_text_cluster_t* cluster = &clusters[i];
            cairo_glyph_t* clusterglyphs = &glyphs[glyph_index];

            // get extents for the glyphs in the cluster
            cairo_text_extents_t extents;
            cairo_scaled_font_glyph_extents(scaled_face, clusterglyphs, cluster->num_glyphs, &extents);
            // ... for later use

            // put paths for current cluster to context
            cairo_glyph_path(cr, clusterglyphs, cluster->num_glyphs);

            // draw black text with green stroke
            peruSetColor(cr,textCol);
            cairo_fill_preserve(cr);
            peruSetColor(cr,strokeCol);
            cairo_set_line_width(cr, strokeSize);
            cairo_stroke(cr);

            // glyph/byte position
            glyph_index += cluster->num_glyphs;
            byte_index += cluster->num_bytes;
        }


    }


};

