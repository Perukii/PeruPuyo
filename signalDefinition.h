
std::set<guint> availKeys={};
int keyTime=0;

static gboolean
keyPressEvent(GtkWidget * widget, GdkEventKey * event, gpointer user_data){
     std::cout<<event->keyval<<std::endl;
     availKeys.insert(event->keyval);

}

static gboolean keyReleaseEvent(GtkWidget * widget, GdkEventKey * event, gpointer user_data){
     availKeys.erase(event->keyval);
}

static gboolean
drawEvent(GtkWidget * widget, cairo_t * cr, gpointer data){
     PERUPUYO_MODE::draw(cr);
}        

static gboolean mouseMoveEvent(GtkWidget *widget,GdkEvent *event, gpointer user_data) {

}

static gboolean
loopEvent(GtkWidget * widget){
    PERUPUYO_MODE::puyoMain.process();
    gtk_widget_queue_draw(widget);
    if(!availKeys.size())keyTime=0;
    else keyTime++;
    for(auto & it:availKeys){
          if(keyTime%PERUPUYO_KEY_UPDATE)break;
          switch(it){
               case 113: //q
                    
                    PERUPUYO_MODE::puyoMain.varyAngl( 1);
                    break;

               case 101: //e
                    PERUPUYO_MODE::puyoMain.varyAngl(-1);
                    break;

               case 100: //d
                    PERUPUYO_MODE::puyoMain.varyPos( 1);
                    break;

               case 97 : //a
                    PERUPUYO_MODE::puyoMain.varyPos(-1);
                    break;
               default:break; 
          }
     
    }
    return true;
}

