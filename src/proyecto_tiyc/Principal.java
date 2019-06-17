/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package proyecto_tiyc;

import java.io.File;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

/**
 *
 * @author pc
 */
public class Principal extends javax.swing.JFrame {
    private static String rutaArchivo;
    private static String nombre;
    /**
     * Creates new form Principal
     * @param ruta path del archivo
     * @param nombre nombre del archivo
     */
    public Principal(String ruta,String nombre) {
        initComponents();
        rutaArchivo=ruta;
        this.nombre=nombre;
        this.nombreArchivo.setText(nombre);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        seleccionar = new javax.swing.JButton();
        nombreArchivo = new javax.swing.JTextField();
        jPanel2 = new javax.swing.JPanel();
        hamming8 = new javax.swing.JButton();
        hamming32 = new javax.swing.JButton();
        hamming1024 = new javax.swing.JButton();
        jLabel4 = new javax.swing.JLabel();
        hamming32768 = new javax.swing.JButton();
        jPanel1 = new javax.swing.JPanel();
        compactar = new javax.swing.JButton();
        descompactar = new javax.swing.JButton();
        jLabel5 = new javax.swing.JLabel();
        jLabel1 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setMaximumSize(new java.awt.Dimension(1350, 768));
        setMinimumSize(new java.awt.Dimension(1350, 768));
        setPreferredSize(new java.awt.Dimension(1350, 768));
        setSize(new java.awt.Dimension(1350, 768));
        getContentPane().setLayout(null);

        jLabel2.setFont(new java.awt.Font("Tahoma", 1, 48)); // NOI18N
        jLabel2.setForeground(new java.awt.Color(240, 240, 240));
        jLabel2.setText("Bienvenido");
        getContentPane().add(jLabel2);
        jLabel2.setBounds(40, 40, 290, 80);

        jLabel3.setFont(new java.awt.Font("Tahoma", 1, 16)); // NOI18N
        jLabel3.setForeground(new java.awt.Color(240, 240, 240));
        jLabel3.setText("Archivo seleccionado:");
        getContentPane().add(jLabel3);
        jLabel3.setBounds(380, 160, 190, 20);

        seleccionar.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        seleccionar.setText("Seleccionar");
        seleccionar.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                seleccionarMouseClicked(evt);
            }
        });
        getContentPane().add(seleccionar);
        seleccionar.setBounds(810, 190, 120, 30);

        nombreArchivo.setEditable(false);
        nombreArchivo.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                nombreArchivoActionPerformed(evt);
            }
        });
        getContentPane().add(nombreArchivo);
        nombreArchivo.setBounds(380, 190, 420, 30);

        jPanel2.setBackground(new java.awt.Color(27, 104, 134));
        jPanel2.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(240, 240, 240), 3));

        hamming8.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        hamming8.setText("Hamming 8");
        hamming8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                hamming8ActionPerformed(evt);
            }
        });

        hamming32.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        hamming32.setText("Hamming 32");
        hamming32.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                hamming32ActionPerformed(evt);
            }
        });

        hamming1024.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        hamming1024.setText("Hamming 1024");
        hamming1024.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                hamming1024ActionPerformed(evt);
            }
        });

        jLabel4.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        jLabel4.setForeground(new java.awt.Color(240, 240, 240));
        jLabel4.setText("Hamming");

        hamming32768.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        hamming32768.setText("Hamming 32768");
        hamming32768.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                hamming32768ActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(jLabel4))
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addGap(74, 74, 74)
                        .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(hamming32, javax.swing.GroupLayout.PREFERRED_SIZE, 190, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(hamming1024, javax.swing.GroupLayout.PREFERRED_SIZE, 190, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(hamming8, javax.swing.GroupLayout.PREFERRED_SIZE, 190, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(hamming32768, javax.swing.GroupLayout.PREFERRED_SIZE, 190, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addContainerGap(80, Short.MAX_VALUE))
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addGap(6, 6, 6)
                .addComponent(jLabel4)
                .addGap(32, 32, 32)
                .addComponent(hamming8, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(hamming32, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(hamming1024, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(hamming32768, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(83, Short.MAX_VALUE))
        );

        getContentPane().add(jPanel2);
        jPanel2.setBounds(720, 250, 350, 410);

        jPanel1.setBackground(new java.awt.Color(27, 104, 134));
        jPanel1.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(240, 240, 240), 3));

        compactar.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        compactar.setText("Compactar archivo");
        compactar.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                compactarMouseClicked(evt);
            }
        });
        compactar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                compactarActionPerformed(evt);
            }
        });

        descompactar.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        descompactar.setText("Descompactar archivo");
        descompactar.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                descompactarMouseClicked(evt);
            }
        });
        descompactar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                descompactarActionPerformed(evt);
            }
        });

        jLabel5.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        jLabel5.setForeground(new java.awt.Color(240, 240, 240));
        jLabel5.setText("Huffman");

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(jLabel5))
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGap(51, 51, 51)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(descompactar, javax.swing.GroupLayout.PREFERRED_SIZE, 190, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(compactar, javax.swing.GroupLayout.PREFERRED_SIZE, 190, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addContainerGap(73, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel5)
                .addGap(88, 88, 88)
                .addComponent(compactar, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(51, 51, 51)
                .addComponent(descompactar, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(125, Short.MAX_VALUE))
        );

        getContentPane().add(jPanel1);
        jPanel1.setBounds(190, 250, 320, 410);

        jLabel1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/hex-abstract-material-design-ad.jpg"))); // NOI18N
        getContentPane().add(jLabel1);
        jLabel1.setBounds(-130, 0, 2090, 2000);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void compactarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_compactarActionPerformed

    }//GEN-LAST:event_compactarActionPerformed

    private void descompactarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_descompactarActionPerformed

    }//GEN-LAST:event_descompactarActionPerformed

    private void hamming1024ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_hamming1024ActionPerformed
        // TODO add your handling code here:
        if (nombreArchivo.getText().length()==0){
            JOptionPane.showMessageDialog(null, "Debe seleccionar un archivo", "Advertencia", JOptionPane.WARNING_MESSAGE);
        }
        else {
            this.setVisible(false);
            new MenuHamming(rutaArchivo,nombreArchivo.getText(),1024).setVisible(true);
        }
    }//GEN-LAST:event_hamming1024ActionPerformed

    private void hamming8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_hamming8ActionPerformed
        // TODO add your handling code here:
        if (nombreArchivo.getText().length()==0){
            JOptionPane.showMessageDialog(null, "Debe seleccionar un archivo", "Advertencia", JOptionPane.WARNING_MESSAGE);
        }
        else {
            this.setVisible(false);
            new MenuHamming(rutaArchivo,nombreArchivo.getText(),8).setVisible(true);
        }
    }//GEN-LAST:event_hamming8ActionPerformed

    private void hamming32ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_hamming32ActionPerformed
        // TODO add your handling code here:
        if (nombreArchivo.getText().length()==0){
            JOptionPane.showMessageDialog(null, "Debe seleccionar un archivo", "Advertencia", JOptionPane.WARNING_MESSAGE);
        }
        else {
            this.setVisible(false);
            new MenuHamming(rutaArchivo,nombreArchivo.getText(),32).setVisible(true);
        }
    }//GEN-LAST:event_hamming32ActionPerformed

    private void compactarMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_compactarMouseClicked
        // TODO add your handling code here:
        if (nombreArchivo.getText().length()==0){
            JOptionPane.showMessageDialog(null, "Debe seleccionar un archivo", "Advertencia", JOptionPane.WARNING_MESSAGE);
        }
        else {
            //FUNCION EN C CON EL PATH ALMACENADO EN rutaArchivo
            JOptionPane.showMessageDialog(null, "El archivo fue compactado con éxito.\n Puedes visualizarlo con el nombre '"+nombreArchivo.getText()+"_comprimido.txt' en el mismo directorio que el archivo original.", "Éxito", JOptionPane.INFORMATION_MESSAGE);
        }
        
    }//GEN-LAST:event_compactarMouseClicked

    private void seleccionarMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_seleccionarMouseClicked
        // TODO add your handling code here:
        JFileChooser selector=new JFileChooser();
        selector.showOpenDialog(null);
        File f= selector.getSelectedFile();
        if (f!=null){
            rutaArchivo=f.getAbsolutePath();
            String nombreAr=f.getName();
            nombreArchivo.setText(nombreAr);
        }
        
        
    }//GEN-LAST:event_seleccionarMouseClicked

    private void nombreArchivoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_nombreArchivoActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_nombreArchivoActionPerformed

    private void hamming32768ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_hamming32768ActionPerformed
        if (nombreArchivo.getText().length()==0){
            JOptionPane.showMessageDialog(null, "Debe seleccionar un archivo", "Advertencia", JOptionPane.WARNING_MESSAGE);
        }
        else {
            this.setVisible(false);
            new MenuHamming(rutaArchivo,nombreArchivo.getText(),32768).setVisible(true);
        }
    }//GEN-LAST:event_hamming32768ActionPerformed

    private void descompactarMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_descompactarMouseClicked
        if (nombreArchivo.getText().length()==0){
            JOptionPane.showMessageDialog(null, "Debe seleccionar un archivo", "Advertencia", JOptionPane.WARNING_MESSAGE);
        }
        else {
            //FUNCION EN C CON EL PATH ALMACENADO EN rutaArchivo
            JOptionPane.showMessageDialog(null, "El archivo fue descompactado con éxito.\n Puedes visualizarlo con el nombre '"+nombreArchivo.getText()+"_descomprimido.txt' en el mismo directorio que el archivo original.", "Éxito", JOptionPane.INFORMATION_MESSAGE);
        }
    }//GEN-LAST:event_descompactarMouseClicked

    
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Principal.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Principal.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Principal.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Principal.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Principal(rutaArchivo,nombre).setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton compactar;
    private javax.swing.JButton descompactar;
    private javax.swing.JButton hamming1024;
    private javax.swing.JButton hamming32;
    private javax.swing.JButton hamming32768;
    private javax.swing.JButton hamming8;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JTextField nombreArchivo;
    private javax.swing.JButton seleccionar;
    // End of variables declaration//GEN-END:variables
}
